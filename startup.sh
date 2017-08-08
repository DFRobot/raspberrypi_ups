#!/bin/sh
sudo cp /dfups/tmp/startupconfig.txt /etc/rc.local
sudo chmod 777 /etc/rc.local
sudo chgrp root /etc/rc.local
sudo chown root /etc/rc.local
