#!/bin/bash
set -eu

TARGET_DIR=rtos_f103_test
TARGET_MCU=NUCLEO_F103RB

mbed compile --source src/$TARGET_DIR/ --source src/common/ --source mbed-os/ -m $TARGET_MCU
st-flash write BUILD/NUCLEO_F103RB/GCC_ARM/$TARGET_DIR.bin 0x8000000 
# sudo cp BUILD/NUCLEO_F446RE/GCC_ARM/$TARGET_DIR.bin /media/usb0/
