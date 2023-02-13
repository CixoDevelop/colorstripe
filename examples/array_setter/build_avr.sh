# Sample build script for AVR architecture. 
# For the example to work on your device, you should change the parameters 
# from the variables below to match your device.

MCU="attiny13"
PIN="2"
LENGHT="100"
STRIPE="WS2812b"
FREQUENCY=9600000

CC="avr-gcc"
DUDE="avrdude"

$CC avr.c -o avr.hex -L../../build-gcc-avr/ -lcolorstripe -I../../headers/ \
    -mmcu=$MCU -DPIN=$PIN -DSTRIPE=$STRIPE -DLENGHT=$LENGHT \
    -Os -DF_CPU=$FREQUENCY

$DUDE -c usbasp -p $MCU -U flash:w:avr.hex
