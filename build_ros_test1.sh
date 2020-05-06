#!/bin/bash
set -eu

TARGET_DIR=ros_test1
TARGET_MCU=NUCLEO_F446RE

mbed compile --source src/$TARGET_DIR/ --source src/common/ --source mbed-os/ --source ros_lib_kinetic -m $TARGET_MCU
#st-flash write BUILD/NUCLEO_F103RB/GCC_ARM/$TARGET_DIR.bin 0x8000000 
sudo cp BUILD/NUCLEO_F446RE/GCC_ARM/$TARGET_DIR.bin /media/usb0/
