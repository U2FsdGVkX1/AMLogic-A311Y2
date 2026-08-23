# -*- coding: utf-8 -*-

import argparse
import json
import sys
import threading
import time
import uuid
from datetime import datetime
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from urllib.parse import urlparse

from amlllm.api import AMLLLM
from amlllm.backend import RunStatus


MODEL_TEMPLATES = {
    "qwen": (
        "<|im_start|>system\nYou are a helpful assistant.<|im_end|>\n",
        "<|im_start|>user\n",
        "<|im_end|>\n<|im_start|>assistant\n",
    ),
    "deepseek": (
        "<|begin_of_sentence|>",
        "<|User|>",
        "<|Assistant|>please don't include <think> tags in your answers\n",
    ),
    "gemma": ("<bos>", "<start_of_turn>user\n", "<end_of_turn>\n<start_of_turn>model\n"),
    "gemma3": ("<bos>", "<start_of_turn>user\n", "<end_of_turn>\n<start_of_turn>model\n"),
    "tiny_llama": (
        "<|im_start|>system\nYou are a friendly chatbot.<|im_end|>\n",
        "<|im_start|>user\n",
        "<|im_end|>\n<|im_start|>assistant\n",
    ),
    "tiny_llama_v0_4": ("", "", ""),
    "phi_1_5": ("", "", "\nAnswer:"),
    "phi_2": ("", "Instruct: ", "\nOutput:"),
}
MODEL_TYPES = ("none", "llama", *MODEL_TEMPLATES.keys())
ROLE_PREFIX = {"system": "System", "assistant": "Assistant", "user": "User"}


def stream_callback(token, userdata=None):
    if not userdata or token.get("status") in (RunStatus.FINISH, RunStatus.ERROR):
        return

    text = token.get("text", "")
    writer = userdata.get("writer")
    if writer and text:
        writer(text)


def model_template(model_type):
    if model_type == "llama":
        date_str = datetime.now().strftime("%d %b %Y")
        return (
            "<|begin_of_text|><|start_header_id|>system<|end_header_id|>\n\n"
            "Cutting Knowledge Date: December 2023\n"
            f"Today Date: {date_str}\n\n"
            "<|eot_id|>",
            "<|start_header_id|>user<|end_header_id|>\n\n",
            "<|eot_id|><|start_header_id|>assistant<|end_header_id|>\n\n",
        )
    return MODEL_TEMPLATES.get(model_type, ("", "", ""))


def apply_model_template(llm, model_type):
    template = model_template(model_type)
    if any(template):
        llm.set_chat_template(*template)


def normalize_content(content):
    if isinstance(content, str):
        return content
    if isinstance(content, list):
        return "\n".join(
            str(part.get("text", ""))
            for part in content
            if isinstance(part, dict) and part.get("type") == "text" and part.get("text")
        )
    return "" if content is None else str(content)


def build_prompt(messages):
    if not isinstance(messages, list) or not messages:
        raise ValueError("messages must be a non-empty array")

    if len(messages) == 1 and messages[0].get("role") == "user":
        return normalize_content(messages[0].get("content")).strip()

    lines = []
    for message in messages:
        if isinstance(message, dict):
            content = normalize_content(message.get("content")).strip()
            if content:
                role = ROLE_PREFIX.get(message.get("role"), "User")
                lines.append(f"{role}: {content}")

    prompt = "\n".join(lines).strip()
    if not prompt:
        raise ValueError("messages must contain text content")
    return prompt


def usage(token_count):
    return {
        "prompt_tokens": 0,
        "completion_tokens": token_count,
        "total_tokens": token_count,
    }


class LLMApp:
    def __init__(self, args):
        self.lock = threading.Lock()
        self.model_name = args.served_model_name
        self.llm = AMLLLM()
        self.llm.config(
            model_path=args.model,
            tokenizer_path=args.tokenizer,
            sampling_mode=args.sampling_mode,
            top_k=args.top_k,
            top_p=args.top_p,
            temperature=args.temperature,
            repeat_penalty=args.repeat_penalty,
            loglevel=args.loglevel,
            on_token=stream_callback,
        )
        self.llm.init()
        apply_model_template(self.llm, args.model_type)

    def close(self):
        self.llm.uninit()

    def generate(self, prompt, writer=None):
        with self.lock:
            return self.llm.run(
                prompt=prompt,
                input_type="prompt",
                run_mode="generate",
                retain_history=False,
                user_data={"writer": writer},
            )


class OpenAIHandler(BaseHTTPRequestHandler):
    server_version = "AmlogicOpenAI/1.0"

    @property
    def app(self):
        return self.server.app

    def do_OPTIONS(self):
        self.send_response(204)
        self.send_cors_headers()
        self.end_headers()

    def do_GET(self):
        path = urlparse(self.path).path
        if path == "/health":
            return self.send_json(200, {"status": "ok"})
        if path == "/v1/models":
            return self.send_json(200, self.models_response())
        self.send_error_json(404, "not found")

    def do_POST(self):
        if urlparse(self.path).path != "/v1/chat/completions":
            return self.send_error_json(404, "not found")

        try:
            payload = self.read_json()
            prompt = build_prompt(payload.get("messages"))
        except ValueError as exc:
            return self.send_error_json(400, str(exc))
        except Exception as exc:
            return self.send_error_json(400, f"invalid request: {exc}")

        if payload.get("stream"):
            self.handle_stream_completion(payload, prompt)
        else:
            self.handle_completion(payload, prompt)

    def models_response(self):
        return {
            "object": "list",
            "data": [
                {
                    "id": self.app.model_name,
                    "object": "model",
                    "created": int(time.time()),
                    "owned_by": "amlogic",
                }
            ],
        }

    def handle_completion(self, payload, prompt):
        completion_id = "chatcmpl-" + uuid.uuid4().hex
        created = int(time.time())
        model = payload.get("model") or self.app.model_name

        try:
            result = self.app.generate(prompt)
        except Exception as exc:
            return self.send_error_json(500, f"generation failed: {exc}")

        text = result.get("text", "")
        token_count = int(result.get("token_count") or 0)
        self.send_json(
            200,
            {
                "id": completion_id,
                "object": "chat.completion",
                "created": created,
                "model": model,
                "choices": [
                    {
                        "index": 0,
                        "message": {"role": "assistant", "content": text},
                        "finish_reason": "stop",
                    }
                ],
                "usage": usage(token_count),
            },
        )

    def handle_stream_completion(self, payload, prompt):
        completion_id = "chatcmpl-" + uuid.uuid4().hex
        created = int(time.time())
        model = payload.get("model") or self.app.model_name
        stream_options = payload.get("stream_options") or {}
        include_usage = bool(stream_options.get("include_usage")) if isinstance(stream_options, dict) else False

        self.send_response(200)
        self.send_header("Content-Type", "text/event-stream")
        self.send_header("Cache-Control", "no-cache")
        self.send_header("Connection", "keep-alive")
        self.send_cors_headers()
        self.end_headers()

        def chunk(delta, finish_reason=None):
            return {
                "id": completion_id,
                "object": "chat.completion.chunk",
                "created": created,
                "model": model,
                "choices": [{"index": 0, "delta": delta, "finish_reason": finish_reason}],
            }

        def write_token(text):
            self.write_sse(chunk({"content": text}))

        try:
            self.write_sse(chunk({"role": "assistant"}))
            result = self.app.generate(prompt, writer=write_token)
            self.write_sse(chunk({}, "stop"))
            if include_usage:
                token_count = int(result.get("token_count") or 0)
                self.write_sse(
                    {
                        "id": completion_id,
                        "object": "chat.completion.chunk",
                        "created": created,
                        "model": model,
                        "choices": [],
                        "usage": usage(token_count),
                    }
                )
            self.wfile.write(b"data: [DONE]\n\n")
            self.wfile.flush()
        except BrokenPipeError:
            self.app.llm.break_generation()
        except Exception as exc:
            self.write_sse({"error": {"message": f"generation failed: {exc}", "type": "server_error"}})

    def read_json(self):
        length = int(self.headers.get("Content-Length", "0"))
        if length <= 0:
            raise ValueError("empty request body")
        if length > 16 * 1024 * 1024:
            raise ValueError("request body too large")
        return json.loads(self.rfile.read(length).decode("utf-8"))

    def send_json(self, status, payload):
        body = json.dumps(payload, ensure_ascii=False).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json")
        self.send_header("Content-Length", str(len(body)))
        self.send_cors_headers()
        self.end_headers()
        self.wfile.write(body)

    def send_error_json(self, status, message):
        self.send_json(
            status,
            {"error": {"message": message, "type": "invalid_request_error", "code": None}},
        )

    def send_cors_headers(self):
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Authorization, Content-Type")

    def write_sse(self, payload):
        self.wfile.write(b"data: " + json.dumps(payload, ensure_ascii=False).encode("utf-8") + b"\n\n")
        self.wfile.flush()

    def log_message(self, fmt, *args):
        sys.stderr.write("%s - - [%s] %s\n" % (self.client_address[0], self.log_date_time_string(), fmt % args))


def parse_args():
    parser = argparse.ArgumentParser(description="Amlogic LLM OpenAI compatible API server")
    parser.add_argument("--model", required=True, help="Path to LLM model file")
    parser.add_argument("--tokenizer", required=True, help="Path to tokenizer resources")
    parser.add_argument("--host", default="0.0.0.0", help="HTTP listen host")
    parser.add_argument("--port", type=int, default=8000, help="HTTP listen port")
    parser.add_argument("--served-model-name", default="qwen2.5-0.5b-instruct", help="Model name exposed by the API")
    parser.add_argument("--sampling-mode", default="argmax", choices=["argmax", "top_p", "top_k"], help="Sampling mode")
    parser.add_argument("--top-k", type=int, default=3, dest="top_k", help="Top-K parameter")
    parser.add_argument("--top-p", type=float, default=0.9, dest="top_p", help="Top-P parameter")
    parser.add_argument("--temperature", type=float, default=1.0, help="Softmax temperature")
    parser.add_argument("--repeat-penalty", type=float, default=1.1, dest="repeat_penalty", help="Repeat penalty factor")
    parser.add_argument("--loglevel", default="ERROR", choices=["DEBUG", "INFO", "WARNING", "ERROR"])
    parser.add_argument("--model-type", default="none", choices=MODEL_TYPES, help="Optional builtin model template")
    return parser.parse_args()


def main():
    args = parse_args()
    app = LLMApp(args)
    httpd = ThreadingHTTPServer((args.host, args.port), OpenAIHandler)
    httpd.app = app

    print(f"Serving {args.served_model_name} on http://{args.host}:{args.port}", flush=True)
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        httpd.server_close()
        app.close()


if __name__ == "__main__":
    sys.exit(main())
