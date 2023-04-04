#!/bin/bash

if [[ $1 == "" ]]; then
    MCU="atmega8"
else
    MCU=$1
fi

if [[ $2 == "" ]]; then
    FREQ="8000000"
else
    FREQ=$2
fi

SOURCES_DIR="../sources/"
SOURCES="colorstripe.c ws2812b_avr.c"

BUILD_DIR="../build-gcc-avr/"
LIB="libcolorstripe.a"

GCC_FLAGS="-Os -mmcu=$MCU -I../libs/avrroutine/headers -DF_CPU=$FREQ"

rm $BUILD_DIR/$LIB -rf
rm $BUILD_DIR/*.o -rf

for file in $SOURCES; do
    avr-gcc $SOURCES_DIR/$file -c -o $BUILD_DIR/$file.o $GCC_FLAGS
done

avr-ar rsc $BUILD_DIR/$LIB $BUILD_DIR/*.o

rm $BUILD_DIR/*.o -rf
