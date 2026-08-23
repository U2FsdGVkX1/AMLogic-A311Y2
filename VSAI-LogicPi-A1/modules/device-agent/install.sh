archive="$BOARD_DIR/modules/device-agent/device-agent.tar.gz"
tar -xzf "$archive" -C "$ROOTFS/opt"
chmod +x "$ROOTFS/opt/device-agent/device-agent"
cp -a "$BOARD_DIR/modules/device-agent/overlay/"* "$ROOTFS/"

chroot_rootfs dnf install -y python3-uv
chroot_rootfs "cd /opt/device-agent-toolkit && uv sync --frozen"
chroot_rootfs systemctl enable device-agent.service device-agent-toolkit.service
