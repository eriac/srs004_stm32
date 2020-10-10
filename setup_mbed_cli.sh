#!/bin/bash

sudo apt install -y mercurial
sudo apt install -y python-pip
pip install mbed-cli
sudo apt install -y gcc-arm-none-e

# sudo reboot



sudo apt-get install -y dh-autoreconf
cd /tmp && git clone https://github.com/texane/stlink
cd /tmp/stlink
./autogen.sh
./configure
make
sudo make install
sudo ldconfig

echo "please sudo reboot"
