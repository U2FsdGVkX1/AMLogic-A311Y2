cp -a "$BOARD_DIR/overlay/"* "$ROOTFS/"

echo 'GRUB_CMDLINE_LINUX="console=ttyS0,921600 earlycon=aml_uart,0xfe07a000"' >> "$ROOTFS/etc/default/grub"
echo "GRUB_DEVICETREE=amlogic/s6_s905d5_bq201_linux.dtb" >> "$ROOTFS/etc/default/grub"