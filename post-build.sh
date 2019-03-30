#!/bin/sh

set -u
set -e

# Add a console on tty1
if [ -e ${TARGET_DIR}/etc/inittab ]; then
    grep -qE '^tty1::' ${TARGET_DIR}/etc/inittab || \
	sed -i '/GENERIC_SERIAL/a\
tty1::respawn:/sbin/getty -L  tty1 0 vt100 # HDMI console' ${TARGET_DIR}/etc/inittab
fi

cp package/busybox/S10mdev ${TARGET_DIR}/etc/init.d/S10mdev
chmod 755 ${TARGET_DIR}/etc/init.d/S10mdev
cp package/busybox/mdev.conf ${TARGET_DIR}/etc/mdev.conf


cp playmusic $TARGET_DIR/usr/bin/
cp S60-playmusic-daemon-service $TARGET_DIR/etc/init.d/
cp playmusic-daemon $TARGET_DIR/usr/bin/

cp -r songs $TARGET_DIR/
cp interfaces $TARGET_DIR/etc/network/

cp sshd_config $TARGET_DIR/etc/ssh/
cp profile $TARGET_DIR/etc/profile
cp wpa_supplicant.conf ${TARGET_DIR}/etc/wpa_supplicant.conf
cp usb ${TARGET_DIR}/

cp Initialize_script ${TARGET_DIR}/

cp Device_check ${TARGET_DIR}/
