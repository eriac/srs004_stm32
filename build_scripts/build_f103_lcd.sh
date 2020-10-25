#!/bin/bash
set -eu

TARGET_DIR=f103_lcd
TARGET_MCU=NUCLEO_F103RB

mbed compile --source src/$TARGET_DIR/ --source src/common/ --source mbed-os/ --source Adafruit_GFX/  -m $TARGET_MCU
st-flash write BUILD/NUCLEO_F103RB/GCC_ARM/$TARGET_DIR.bin 0x8000000 
