kernel_version=$(basename "$BUILD_DIR/kernel/modules/lib/modules/"*)
cp -a "$BOARD_DIR/modules/adla/overlay/"* "$ROOTFS/"
install -m 0644 "$MODULE_DIR/adla/kmd/adla_core.ko" "$ROOTFS/lib/modules/$kernel_version/kernel/"
