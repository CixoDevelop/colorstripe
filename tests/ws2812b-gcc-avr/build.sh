#!/bin/bash

MCU=atmega8
FREQUENCY=8000000

avr-gcc -DF_CPU=$FREQUENCY -I../../headers core.c -o core.hex -Os \
-mmcu=$MCU -L../../build-gcc-avr -lcolorstripe  -I../../libs/stdavr/headers \
-L../../libs/stdavr/build-avr-gcc -lstdavr

sudo avrdude -c usbasp -p $MCU -U flash:w:core.hex
