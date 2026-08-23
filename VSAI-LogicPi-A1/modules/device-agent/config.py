from pathlib import Path

from hox import ConfigContext, Module


def configure(ctx: ConfigContext) -> Module:
    return Module(
        name="device-agent",
        install_after=["image-rootfs"],
        requires=["tar"],
        install=[Path(__file__).parent / "install.sh"],
    )
