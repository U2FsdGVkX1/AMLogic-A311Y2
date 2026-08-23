kernel_version=$(basename "$BUILD_DIR/kernel/modules/lib/modules/"*)

cp -a "$BOARD_DIR/modules/w2l/overlay/"* "$ROOTFS/"
install -d "$ROOTFS/lib/firmware/w2l"
install -m 0644 "$BOARD_DIR/modules/w2l/source/common"/*.txt "$ROOTFS/lib/firmware/w2l/"
install -m 0644 "$BOARD_DIR/modules/w2l/source/common"/wifi_w2l_fw_*.bin "$ROOTFS/lib/firmware/w2l/"
install -m 0644 "$BOARD_DIR/modules/w2l/source/common/aml_wifi_rf.txt" "$ROOTFS/lib/firmware/aml_wifi_rf.txt"
install -m 0644 "$MODULE_DIR/aml_drv/fullmac"/*.ko "$ROOTFS/lib/modules/$kernel_version/kernel/"
