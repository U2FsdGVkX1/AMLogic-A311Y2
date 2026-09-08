from pathlib import Path

from actions import cp, git, shell
from hox import ConfigContext, Module

ARTIFACTS = (
    "u-boot.bin.signed",
    "u-boot.bin.sd.bin.signed",
    "u-boot.bin.usb.signed",
    "s6_bq201-u-boot.aml.zip",
)


def configure(ctx: ConfigContext) -> Module:
    return Module(
        name="uboot",
        requires=["git", "make", "zip", "python3", "openssl", "xxd"],
        # CONFIG_BYPASS_AOCPU=y: skip bl30 source build (no riscv toolchain)
        env={
            "CROSS_COMPILE": "aarch64-linux-gnu-",
            "ARCH": "arm",
            "CONFIG_BYPASS_AOCPU": "y",
            "KCFLAGS": "-DCONFIG_YOCTO",
        },
        build=[
            git(
                src="git@github.com:U2FsdGVkX1/AMLogic-A311Y2_uboot.git",
                path=Path("."),
            ),
            shell(cmds=["./mk s6_bq201"]),
            *[cp(src=Path("build") / name, dest=Path(".")) for name in ARTIFACTS],
        ],
        install=[
            f'cp -f "$MODULE_DIR/{name}" $OUTPUT_DIR' for name in ARTIFACTS
        ],
    )
