# ColorStripe library

It is a library for handling various addressable led strips. Currently has
support for:
 * WS2812b (tested)
 * WS2812 (not tested, but code from WS2812b should work)

When it comes to microcontrollers, the following are supported:
 * AVR (8Mhz, 9.6Mhz, 16Mhz)

Support in the future will be developed with new families of microcontrollers 
and new types of LED strips that only fall into my hands.

The library can be run on AtTiny13, and thanks to the functional approach to 
setting the colors of the LEDs, it is possible to control any number of LEDs.


## How to add it to my project?

When using a library, you need to start with compilation, which is to generate 
an .a file with the library, then add that file as an object when linking, 
and the library headers/ directory to the compilation. To build the library, go 
to the build-(target) directory and then edit the config.sh file to suit your 
project needs. Most important to change:
 * FREQUENCY - The frequency with which the microcontroller works expressed 
   in Hz. So, for example, for 8MHz FREQUENCY=8000000
 * MCU - Target Microcontroller. The name depends on the architecture, so 
   there are more detailed descriptions in each target.

After changing the settings you should call ./build.sh and the library will be 
built. Attention, after each change of the operating frequency and or of the 
microcontroller, the library must be recompiled!!!

### Support libs
 * AVR - stdavr, You must build it and add it to Your project also. It is in
         libs/ dir.

## How to start coding for it?

You can see the examples which are also used to test the functioning of the 
library. These examples are available in the examples directory, if you like 
to learn by reading examples instead of tutorials, then look in the directory 
mentioned above, find the example that best suits your project. However, if 
you prefer guided learning, read on.


## ColorStripe tutorial

Let's start by creating a structure that holds a strip of LEDs.


### Creating stripe structure

```
colorstripe_t stripe;
colorstripe_init(&stripe, STRIPE_TYPE_sender, STRIPE_PIN, LED_NUMBERS);
```

Where:
 * STRIPE_TYPE_sender - sender function. That determine stripe type. For 
   example, when created stripe should be WS2812b, then use ws2812b_sender.
 * STRIPE_PIN - That is pin for stripe.
 * LED_NUMBERS - Determinate how much leds have stripe.

The structure of the colorstripe_t type created in this way is a representation 
of the led strip in the project. It is then used by other library functions to 
send data to the led strip.

### Pins select
 * AVR - For this architecture, lib use stdavr lib to manipulating pins. You
         can use PIN_x definition to select pin by chip physical pin. For
         example, PIN_6 is 6 physical pin o device.

So let's send some data to the diodes.

```
color_t colors[] = {{0x7F, 0x45, 0xCB}, {0x00, 0xB7, 0xD4}};
colorstripe_array_setter(&stripe, colors, sizeof(colors) / sizeof(color_t));
```

Who will set all LEDs to colors #FFC0CB alternating with #00B7D4. The 
colorstripe_array_setter function takes as parameters:
 * Pointer on led strip structure
 * An indicator for the color storage table
 * The size of this array

An example of how to write a project whose only task is to send such data 
to the LED strip can be found in the directory "examples/array_setter/"

However, on very small microcontrollers, where the entire strip as an array 
would not fit in any case, a much better choice is to use the functional 
method of color determination. This allows you to at least run a string 
of 150 LEDs, which a table of colors, where each LED has its own hue, 
would take up 450 bytes on a microcontroller with 64 bytes of RAM. So it 
is a memory saving method.

The method of functionally setting the colors of the LEDs in the strip 
requires the creation of a function that accepts the following as 
parameters:
 * (unsigned int) - currently processed diode
 * (unsigned int) - the length of the entire bar

This function must then return a color_t structure, where the new color 
of this LED will be. An example of such a function:

```
color_t setter(unsigned int count, unsigned int lenght) {
    color_t color;

    color.red = 0xFF;
    color.green = count % 0xFF;
    color.blue = 0xFF - color.green;

    return color;
}
```

Now that we have created such a function, we can use it to set new colors 
for the leds, as shown in the example:

```
colorstripe_functional_setter(&stripe, setter);
```

Additional considerations for creating such functions:
 * The function cannot be performed for too long, because after some time 
   the diodes state that it is the end of the transmission of a new sequence 
   of colors, and sending new data will result in setting the diodes anew. 
   It is easy to recognize such an exception, because some of the LEDs will 
   not be lit, or only the first of them will be lit.
 * The function can have static variables, which allows you to create more 
   complex animations. To create one, loop the colorstripe_functional_setter 
   call in a loop with some time between calls, and also use the static 
   variables described above.
 * The function can use variables from the glonal space. This can be useful 
   when arranging animations based on, for example, data from buttons.

An example of using this method can be found in "examples/functional_setter/"
