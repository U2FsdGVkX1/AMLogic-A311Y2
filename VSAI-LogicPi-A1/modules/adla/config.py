from pathlib import Path

from actions import cp, make
from hox import ConfigContext, Module


def configure(ctx: ConfigContext, kernel_env: dict[str, str]) -> Module:
    module_dir = Path(__file__).parent
    return Module(
        name="adla",
        build_after=["kernel"],
        install_after=["kernel"],
        install_before=["image-kernel"],
        requires=["make"],
        env=kernel_env,
        build=[
            cp(src=module_dir / "source", dest="."),
            make(args="KDIR=../kernel Building_Yocto=1 modules"),
        ],
        install=[module_dir / "install.sh"],
    )
