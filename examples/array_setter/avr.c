#include <stdbool.h>
#include <colorstripe.h>
#include <stdavr.h>

/* Stripe selector */
#if STRIPE==WS2812b
#define STRIPE_SENDER ws2812b_sender
#endif

/** \fn main
 * This example shows how you can send a static array of data to the 
 * LED strip.
 */
int main() {

    /* Create stripe */
    colorstripe_t stripe;
    colorstripe_init(&stripe, STRIPE_SENDER, PIN_NUMBER, LENGHT);

    /* Create array of colors, and send it */
    color_t colors[] = {{0x7F, 0x45, 0x99}, {0x00, 0xB7, 0xD4}};
    colorstripe_array_setter(
        &stripe, colors, 
        sizeof(colors) / sizeof(color_t)
    );

    /* End */
    while (true) ;
}
