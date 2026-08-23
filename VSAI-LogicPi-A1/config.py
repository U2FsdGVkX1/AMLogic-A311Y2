from boards.common import KERNEL_INSTALL, default_images, default_partitions, firmware
from hox import Board, ConfigContext


def configure(ctx: ConfigContext) -> Board:
    arch = "aarch64"
    fw = firmware(arch)
    kernel = fw.kernel(
        "git@github.com:U2FsdGVkX1/AMLogic-A311Y2_kernel.git",
        "vsai_bq201_defconfig",
        install=[KERNEL_INSTALL, ctx.BOARD_DIR / "install.sh"],
    )
    modules = ctx.adapter + [
        kernel,
        ctx.module("gpu", kernel.env),
        ctx.module("adla", kernel.env),
        ctx.module("w2l", kernel.env),
        ctx.module("uboot"),
    ]

    # The qwen and device-agent modules fetch their artifacts from overseas
    # sources (GitHub Raw, HuggingFace, PyPI). Skip them under -p china so the
    # build only relies on China-reachable mirrors.
    if ctx.params.get("china") != "true":
        modules.append(ctx.module("qwen"))
        modules.append(ctx.module("device-agent"))

    return Board(
        arch=arch,
        partitions=default_partitions(),
        images=default_images(),
        modules=modules,
    )
