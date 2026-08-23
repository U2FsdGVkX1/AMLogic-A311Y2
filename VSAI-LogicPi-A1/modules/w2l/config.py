from pathlib import Path

from actions import cp, make, patch
from hox import ConfigContext, Module


def configure(ctx: ConfigContext, kernel_env: dict[str, str]) -> Module:
    module_dir = Path(__file__).parent
    return Module(
        name="w2l",
        build_after=["kernel"],
        install_after=["kernel"],
        install_before=["image-kernel"],
        requires=["make", "patch"],
        env=kernel_env,
        build=[
            cp(src=module_dir / "source", dest="."),
            patch(patches=[module_dir / "patches/fix-mkvers-for-sdk-import.patch"]),
            make(args="-C ../kernel M=$PWD/aml_drv CONFIG_BUILDROOT=y modules"),
        ],
        install=[module_dir / "install.sh"],
    )
