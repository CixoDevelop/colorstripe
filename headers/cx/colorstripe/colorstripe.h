/*
 * This project is a library for addressable LED strips. Allows you to use 
 * different LED strips on different families of microcontrollers.
 *
 * Author: Cixo
 */

#ifndef COLORSTRIPE_H_INCLUDED
#define COLORSTRIPE_H_INCLUDED

#include <stdint.h>

/** \struct color_s color_t
 * This struct store color.
 */
typedef struct color_s {

    /* Red color */
    uint8_t red;

    /* Green color */
    uint8_t green;

    /* Blue color */
    uint8_t blue;

} color_t;

/** \struct colorstripe_s colorstripe_t
 * This struct store single stripe.
 */
typedef struct colorstripe_s {
    
    /* This is pin number */
    uint8_t pin;

    /* This is stripe lenght */
    unsigned int lenght;

    /* this is sender for stripe */
    void (*sender)(uint8_t pin, color_t color);

} colorstripe_t;

/** \fn colorstripe_init
 * This function initializes the led strip structure.
 * @param *stripe Stripe structure to setup 
 * @param *sender Sender function for stripe, that is determinate by stripe
 * @param pin Pin number to work with
 * @param lenght Stripe lenght
 */
void colorstripe_init(
    colorstripe_t * stripe, 
    void (*sender)(uint8_t, color_t),
    uint8_t pin,
    unsigned int lenght
);

/** \fn colorstripe_functional_setter
 * This function sends the colors calculated in real time by the function to 
 * the LEDs of the strip. This is a function that takes as parameters the 
 * diode number, the length of the strip, and returns color_t.
 * @param *stripe Stripe to send data
 * @param *setter Setter function 
 */
void colorstripe_functional_setter(
    colorstripe_t *stripe, 
    color_t (*setter)(unsigned int, unsigned int)
);

/** \fn colorstripe_array_setter
 * This sets up a strip of LEDs from the local array. As parameters it 
 * accepts the address of this array and its size. If the size of the array 
 * is smaller than the length of the bar, then the pattern will repeat to 
 * fill the entire bar.
 * @param *stripe Stripe to send data
 * @param *array Array to send from
 * @param lenght Array lenght
 */
void colorstripe_array_setter(
    colorstripe_t *stripe,
    color_t *array,
    unsigned int lenght
);

#endif
