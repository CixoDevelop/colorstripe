#ifndef WS2812B_H_INCLUDED
#define WS2812B_H_INCLUDED

#include <stdint.h>
#include "colorstripe.h"

/** \fn ws2812b_sender 
 * This function is a data sender for ws2812b led strip. Set it as the sender 
 * if the tape in the project is ws2812b.
 * @pin Pin to send on
 * @color Color to send
 */
void ws2812b_sender(uint8_t pin, color_t color);

#endif
