#!/bin/bash

MCU=attiny13
FREQUENCY=9600000

avr-gcc -DF_CPU=$FREQUENCY -I../../headers core.c -o core.hex -Os \
-mmcu=$MCU -L../../build-gcc-avr -lcolorstripe 

sudo avrdude -c usbasp -p $MCU -U flash:w:core.hex
