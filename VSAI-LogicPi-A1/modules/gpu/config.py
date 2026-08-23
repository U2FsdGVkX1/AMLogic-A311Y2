from pathlib import Path

from actions import cp, make
from hox import ConfigContext, Module


def configure(ctx: ConfigContext, kernel_env: dict[str, str]) -> Module:
    module_dir = Path(__file__).parent
    extra_cflags = " ".join([
        "-DCONFIG_MALI_DEVFREQ",
        "-DCONFIG_MALI_GATOR_SUPPORT",
        "-DCONFIG_MALI_REAL_HW",
        "-I$PWD/valhall/r44p0/kernel/include",
        "-DCONFIG_MALI_LOW_MEM=0",
    ])
    make_args = " ".join([
        "-C ../kernel",
        "M=$PWD/valhall/r44p0/kernel/drivers",
        f'EXTRA_CFLAGS="{extra_cflags}"',
        "CONFIG_MALI_MIDGARD=m",
        "CONFIG_MALI_DEVFREQ=y",
        "CONFIG_MALI_GATOR_SUPPORT=y",
        "CONFIG_MALI_REAL_HW=y",
        "CONFIG_MALI_CSF_SUPPORT=y",
        "CONFIG_MALI_MEMORY_GROUP_MANAGER=y",
        "CONFIG_MALI_PROTECTED_MEMORY_ALLOCATOR=y",
        "CONFIG_MALI_PLATFORM_NAME=devicetree",
        "modules",
    ])
    return Module(
        name="gpu",
        build_after=["kernel"],
        install_after=["kernel"],
        install_before=["image-kernel"],
        requires=["make", "patchelf"],
        env=kernel_env,
        build=[
            cp(src=module_dir / "source", dest="."),
            make(args=make_args),
        ],
        install=[module_dir / "install.sh"],
    )
