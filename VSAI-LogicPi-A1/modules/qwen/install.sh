cp -a "$BOARD_DIR/modules/qwen/overlay/"* "$ROOTFS/"

amllm_dir="$ROOTFS/usr/share/amllm"
wheel="amlllm-1.0.0-cp310-cp310-linux_aarch64.whl"
model="Qwen2.5-0.5B-Instruct_quant_i8_s905x5.adla"

install -d "$amllm_dir"
curl -fL "https://raw.githubusercontent.com/Amlogic-NN/amlnn-toolkit/main/amlnn_edge_toolkit_lite/whl/amlllm-1.0.0-cp310-cp310-linux_aarch64.whl" \
    -o "$amllm_dir/$wheel"
curl -fL "https://huggingface.co/Amlogic-NN/Qwen2.5-0.5B-Instruct_quant_i8/resolve/main/Qwen2.5-0.5B-Instruct_quant_i8_s905x5.adla" \
    -o "$amllm_dir/$model"
curl -fL "https://huggingface.co/Amlogic-NN/Qwen2.5-0.5B-Instruct_quant_i8/resolve/main/qwen2.5_0.5B/tokenizer.json" \
    -o "$amllm_dir/tokenizer.json"

chroot_rootfs dnf install -y python3.10
chroot_rootfs python3.10 -m ensurepip --upgrade
chroot_rootfs python3.10 -m pip install --force-reinstall "/usr/share/amllm/$wheel"
chroot_rootfs systemctl enable amllm.service
