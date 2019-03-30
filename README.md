# Buildroot-MP3-Music-Player
Advanced MP3 Player using Bluetooth Speaker, Buildroot and Raspberry-pi3

The project consists of three scripts and C file, the first script run on boot to call two other scripts the first one is the Initialize_script 
which starts up the blueooth services.The other one is the usb script hich scans the usb ports and get all the .mp3 files
Then, the user connect his bluetooth device.after that, he should start the program which controls the mp3 player.

Wifi Configuraions:
- add this lines to your Post-build script:
cp package/busybox/S10mdev ${TARGET_DIR}/etc/init.d/S10mdev
chmod 755 ${TARGET_DIR}/etc/init.d/S10mdev
cp package/busybox/mdev.conf ${TARGET_DIR}/etc/mdev.conf
- select rpi-wifi-firmware from buildroot menuconfig
- select wpa supplicant in buildroot configuraions

- edit wpa_supplicant.conf :

country=BE
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
network={
  ssid="Your SSId"
  psk="Your Password"
  key_mgmt=WPA-PSK
}

- install wall and openssh
Bluetooth Configuraions:

- select rpi-bt-firmware from buildroot menuconfig.
- also select the bt43-firmware and sbc.
- install bluez 5 from buildroot menuconfig.
- edit cmdline.txt to be like this:
root=/dev/mmcblk0p2 rootwait console=tty1 console=serial0,115200 

Audio Configurations: 

- install alsa-utils and alsa lib from buildroot menuconfig.
- install bluez-alsa to stream audio through bluetooth.
- install mpg123 audio player.
- install espeak for text to speech.
