#!/bin/bash
set -eu

TARGET_DIR=srs_wl
TARGET_MCU=NUCLEO_F446RE
TOOLCHAIN=GCC_ARM

mbed compile --source src/$TARGET_DIR/ --source src/common/ --source mbed-os/ --source MPU6050 -m $TARGET_MCU -t $TOOLCHAIN
st-flash write BUILD/$TARGET_MCU/GCC_ARM/$TARGET_DIR.bin 0x8000000 
