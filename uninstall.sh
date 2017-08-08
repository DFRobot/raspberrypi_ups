#!/bin/sh
sudo rm /usr/lib/libdfups.so
sudo rm /usr/include/dfups.h
sudo rm /usr/bin/ups
sudo rm /usr/local/lib/python2.7/dist-packages/_dfups.so
file="/dfups/tmp/rc.txt"
if [ -f "$file" ]
then
	sudo cp /dfups/tmp/rc.txt /etc/rc.local
fi	
sudo rm -rf /dfups
rm -rf /home/pi/raspberrypi_ups
