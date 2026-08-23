from pathlib import Path

from hox import ConfigContext, Module


def configure(ctx: ConfigContext) -> Module:
    return Module(
        name="qwen",
        install_after=["image-rootfs"],
        requires=["curl"],
        install=[Path(__file__).parent / "install.sh"],
    )
