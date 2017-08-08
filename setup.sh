#!/bin/sh
chmod +x startup.sh
sudo mkdir -p /dfups/tmp
file="/dfups/tmp/rc.txt"
if [ ! -f "$file" ]
then
	sudo cp /etc/rc.local /dfups/tmp/rc.txt
fi
gcc -fPIC -shared dfups.c -o libdfups.so
gcc ups_wdog.c -o ups_wdog -lwiringPi
sudo mv libdfups.so /usr/lib
sudo cp dfups.h /usr/include
sudo cp /etc/rc.local /dfups/tmp/startupconfig.txt
sudo mv ups_wdog /dfups
sudo cp startup.sh /dfups
gcc setup.c -o setup -lwiringPi
sudo ./setup
sudo cp /dfups/tmp/startupconfig.txt /etc/rc.local
rm setup
gcc example/ups.c -o ./example/ups -ldfups -lwiringPi
gcc example/ups_count.c -o ./example/ups_count
sudo cp example/ups /usr/bin/
sudo cp pythonups/lib/_dfups.so /usr/local/lib/python2.7/dist-packages/

