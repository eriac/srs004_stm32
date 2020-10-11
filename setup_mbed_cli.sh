#!/bin/bash

# install mbed-cli & related
sudo apt install -y mercurial
sudo apt install -y python-pip
pip install mbed-cli
sudo apt install -y gcc-arm-none-embi

# install stlink-driver
sudo apt-get install -y dh-autoreconf
cd /tmp && git clone https://github.com/texane/stlink
cd /tmp/stlink
./autogen.sh
./configure
make
sudo make install
sudo ldconfig

echo "please sudo reboot"
