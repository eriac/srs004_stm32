#!/bin/bash
set -eu

TARGET_DIR=srs_pw
TARGET_MCU=NUCLEO_F103RB

mbed compile --source src/$TARGET_DIR/ --source src/common/ --source mbed-os/ --source ADXL345_I2C/ -m $TARGET_MCU -t GCC_ARM
st-flash write BUILD/NUCLEO_F103RB/GCC_ARM/$TARGET_DIR.bin 0x8000000 
