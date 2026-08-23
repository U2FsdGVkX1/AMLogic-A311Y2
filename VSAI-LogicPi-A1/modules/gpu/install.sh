kernel_version=$(basename "$BUILD_DIR/kernel/modules/lib/modules/"*)

chroot_rootfs dnf install -y startup-notification libeis

install -d "$ROOTFS/var/tmp/mutter-rpms"
install -m 0644 "$BOARD_DIR/modules/gpu/mutter-rpms/mutter-common-50.1-1.fc44.noarch.rpm" "$ROOTFS/var/tmp/mutter-rpms/"
install -m 0644 "$BOARD_DIR/modules/gpu/mutter-rpms/mutter-50.1-1.fc44.aarch64.rpm" "$ROOTFS/var/tmp/mutter-rpms/"
chroot_rootfs rpm -Uvh --nodeps --replacepkgs \
    /var/tmp/mutter-rpms/mutter-common-50.1-1.fc44.noarch.rpm \
    /var/tmp/mutter-rpms/mutter-50.1-1.fc44.aarch64.rpm
rm -rf "$ROOTFS/var/tmp/mutter-rpms"

install -d \
    "$ROOTFS/usr/lib64/mali" \
    "$ROOTFS/lib/modules/$kernel_version/kernel/drivers/arm/gpu"
cp -a "$BOARD_DIR/modules/gpu/overlay/"* "$ROOTFS/"

install -m 0644 "$BOARD_DIR/modules/gpu/mali/libMali_dmaheap.so" "$ROOTFS/usr/lib64/mali/libMali.so"
install -m 0644 "$BOARD_DIR/modules/gpu/mali/mali_csffw.bin" "$ROOTFS/usr/lib/firmware/mali_csffw.bin"
for soname in libEGL.so.1 libGLESv1_CM.so.1 libGLESv2.so.2 libgbm.so.1; do
    cp "$ROOTFS/usr/lib64/mali/libMali.so" "$ROOTFS/usr/lib64/mali/$soname"
    patchelf --set-soname "$soname" "$ROOTFS/usr/lib64/mali/$soname"
    ln -snf "$soname" "$ROOTFS/usr/lib64/mali/${soname%.*}"
done

chroot_rootfs ldconfig

install -m 0644 "$MODULE_DIR/valhall/r44p0/kernel/drivers/gpu/arm/midgard/mali_kbase.ko" \
    "$ROOTFS/lib/modules/$kernel_version/kernel/drivers/arm/gpu/mali.ko"
install -m 0644 "$MODULE_DIR/valhall/r44p0/kernel/drivers/base/arm/memory_group_manager/memory_group_manager.ko" \
    "$ROOTFS/lib/modules/$kernel_version/kernel/drivers/arm/gpu/memory_group_manager.ko"
install -m 0644 "$MODULE_DIR/valhall/r44p0/kernel/drivers/base/arm/protected_memory_allocator/protected_memory_allocator.ko" \
    "$ROOTFS/lib/modules/$kernel_version/kernel/drivers/arm/gpu/protected_memory_allocator.ko"
