#include <stdint.h>
#include <stdlib.h>
#include <colorstripe.h>
#include <util/delay.h>

/** \fn functional_tester
 * This is test for functional setter. It run very simple animation.
 * @count Current diode in stripe
 * @lenght Stripe lenght
 */
color_t functional_tester(unsigned int count, unsigned int lenght) {
    static unsigned int current = 0x00;
    static int8_t direction = 1;
    static uint8_t proportion = 0x00;

    if (proportion == 0x00) proportion = 0xFF / lenght;

    uint8_t power = proportion * abs(count - current);

    if (count == 0x00) {
        current += direction;

        if (current == lenght - 1) direction = -1;
        if (current == 0x00) direction = 1;
    }

    return (color_t) {power, 0x00, 0xFF - power};
}

/** \fn main
 * This function create stripe, send array of colors to it, then
 * array setter is testing, then run functional setter for simple animation,
 * and functional setter is testing.
 */
int main() {
    colorstripe_t stripe;
    colorstripe_init (
        &stripe, 
        ws2812b_sender, 
        AVR_CALC_PIN_NUMBER(&PORTB, 2), 
        144
    );

    color_t colors[] = {{0xFF, 0x00, 0xFF}, {0x11, 0x22, 0x33}};
    colorstripe_array_setter(&stripe, colors, 2);

    _delay_ms(1000);

    while (1) {
        colorstripe_functional_setter(&stripe, functional_tester);
        _delay_ms(10);
    }
}

