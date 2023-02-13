#include <stdint.h>
#include "colorstripe.h"

/** \def delay_us
 * This is macro to run delay_us, this is useable for delay after send one
 * frame to stripe.
 */
#ifdef __AVR_ARCH__

/* For AVR */
#include <util/delay.h>
#define colorstripe_delay_us(X) _delay_us((X))

#endif

/** \fn colorstripe_init
 * This function initializes the led strip structure.
 * @*stripe Stripe structure to setup 
 * @*sender Sender function for stripe, that is determinate by stripe type
 * @pin Pin number to work with
 * @lenght Stripe lenght
 */
void colorstripe_init(
    colorstripe_t * stripe, 
    void (*sender)(uint8_t, color_t),
    uint8_t pin,
    unsigned int lenght
) {
    stripe->pin = pin;
    stripe->sender = sender;
    stripe->lenght = lenght;
}

/** \fn colorstripe_functional_setter
 * This function sends the colors calculated in real time by the function to 
 * the LEDs of the strip. This is a function that takes as parameters the 
 * diode number, the length of the strip, and returns color_t.
 * @*stripe Stripe to send data
 * @*setter Setter function 
 */
void colorstripe_functional_setter(
    colorstripe_t *stripe, 
    color_t (*setter)(unsigned int, unsigned int)
) {
    for (unsigned int count = 0; count < stripe->lenght; ++count) {
        stripe->sender(stripe->pin, setter(count, stripe->lenght));
    }

    colorstripe_delay_us(900);
}

/** \fn colorstripe_array_setter
 * This sets up a strip of LEDs from the local array. As parameters it 
 * accepts the address of this array and its size. If the size of the array 
 * is smaller than the length of the bar, then the pattern will repeat to 
 * fill the entire bar.
 * @*stripe Stripe to send data
 * @*array Array to send from
 * @lenght Array lenght
 */
void colorstripe_array_setter(
    colorstripe_t *stripe,
    color_t *array,
    unsigned int lenght
) {
    for (unsigned int count = 0; count < stripe->lenght; ++count) {
        stripe->sender(stripe->pin, array[count % lenght]);
    }

    colorstripe_delay_us(900);
}
