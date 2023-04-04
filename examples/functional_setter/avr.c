#include <stdlib.h>
#include <stdbool.h>
#include <util/delay.h>
#include <cx/avrroutine.h>
#include <cx/colorstripe.h>

/* Stripe selector */
#if STRIPE==WS2812b
#define STRIPE_SENDER ws2812b_sender
#endif

/** \fn blinking 
 * This function is useful for setting animation values for successive LEDs. 
 * Each time the function is called, we calculate the next animation step.
 * @count Count of current processing led
 * @lenght Lenght of led strip
 */
color_t blinking(unsigned int count, unsigned int lenght) {
    
    /* Current animation step */
    static unsigned int current = 0x00; 
    
    /* Current animation direction */
    static signed int direction = 0x01;
    
    /* 
     * Proportion for animation calc. This would be calculate 
     * only once, because this operation take to many time. 
     */
    static uint8_t proportion = 0x00;

    /* If it is first loop, then calc proportion */
    if (!proportion) proportion = 0xFF / lenght;

    /* Calc power for this led */
    uint8_t power = proportion * abs(current - count);

    /* If it is first led, then move to next step */
    if (count == 0x00) {
        
        /* Next step */
        current = current + direction;
        
        /* If it is extreme values, then change direction */
        if (current == lenght - 1) direction = -1;
        if (current == 0x00) direction = 1;
    
    }

    /* Return white color with calculate power */
    return (color_t) {power, power, power};
}

/** \fn main
 * This example shows how you can send a static array of data to the 
 * LED strip.
 */
int main() {

    /* Create stripe */
    colorstripe_t stripe;
    colorstripe_init(&stripe, STRIPE_SENDER, PIN_NUMBER, LENGHT);

    /* Run animation in loop */
    while (true) {
        colorstripe_functional_setter(&stripe, blinking);
        
        /* Animation frame time */
        _delay_ms(300);
    }

    /* End */
    while (true) ;
}
