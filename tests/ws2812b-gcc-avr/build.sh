# Sample build script for AVR architecture. 
# For the example to work on your device, you should change the parameters 
# from the variables below to match your device.

MCU="atmega8"
PIN="PIN_6"
LENGHT="100"
STRIPE="WS2812b"
FREQUENCY=8000000

CC="avr-gcc"
DUDE="avrdude"

$CC core.c -o core.hex -L../../build-gcc-avr/ -lcolorstripe -I../../headers/ \
    -mmcu=$MCU -DPIN_NUMBER=$PIN -DSTRIPE=$STRIPE -DLENGHT=$LENGHT \
    -Os -DF_CPU=$FREQUENCY -L../../libs/avrroutine/build-avr-gcc/ \
    -lavrroutine -I../../libs/avrroutine/headers

$DUDE -c usbasp -p $MCU -U flash:w:avr.hex
