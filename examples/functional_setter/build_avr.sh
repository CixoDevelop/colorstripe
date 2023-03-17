# Sample build script for AVR architecture. 
# For the example to work on your device, you should change the parameters 
# from the variables below to match your device.

MCU="atmega8"
PIN="PIN_6"
LENGHT="100"
STRIPE="WS2812b"
FREQUENCY=800000

CC="avr-gcc"
DUDE="avrdude"

$CC avr.c -o avr.hex -L../../libs/stdavr/build-avr-gcc/ \
    -L../../build-gcc-avr/ -lcolorstripe -I../../libs/stdavr/headers/ \
    -I../../headers/ -lstdavr \
    -mmcu=$MCU -DSTRIPE=$STRIPE -DLENGHT=$LENGHT \
    -Os -DPIN_NUMBER=$PIN -DF_CPU=$FREQUENCY

$DUDE -c usbasp -p $MCU -U flash:w:avr.hex
