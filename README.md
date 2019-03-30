# Buildroot-MP3-Music-Player
Advanced MP3 Player using Bluetooth Speaker, Buildroot and Raspberry-pi3

The project consists of three scripts and C file, the first script run on boot to call two other scripts the first one is the Initialize_script 
which starts up the blueooth services.The other one is the usb script hich scans the usb ports and get all the .mp3 files
Then, the user connect his bluetooth device.after that, he should start the program which controls the mp3 player.

Wifi Configuraions:
1- add this lines to your Post-build script:

cp package/busybox/S10mdev ${TARGET_DIR}/etc/init.d/S10mdev
chmod 755 ${TARGET_DIR}/etc/init.d/S10mdev
cp package/busybox/mdev.conf ${TARGET_DIR}/etc/mdev.conf

2- select rpi-wifi-firmware from buildroot menuconfig
3- select wpa supplicant in buildroot configuraions
4- edit wpa_supplicant.conf :

country=BE
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
 
network={
  ssid="Your SSId"
  psk="Your Password"
  key_mgmt=WPA-PSK
}

5- install wall and openssh

Bluetooth Configuraions:
1- select rpi-bt-firmware from buildroot menuconfig.
2- also select the bt43-firmware and sbc.
3- install bluez 5 from buildroot menuconfig.
4- edit cmdline.txt to be like this:
root=/dev/mmcblk0p2 rootwait console=tty1 console=serial0,115200 

Audio Configurations: \n
1- install alsa-utils and alsa lib from buildroot menuconfig.\n
2- install bluez-alsa to stream audio through bluetooth.\n
3- install mpg123 audio player.\n
4- install espeak for text to speech.\n
