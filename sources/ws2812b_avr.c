/* This file store code only for AVR */
#ifdef __AVR_ARCH__

#include <stdint.h>
#include <avr/io.h>
#include <stdavr.h>
#include "colorstripe.h"
#include "ws2812b.h"

/* To use lib, F_CPU must be define */
#ifndef F_CPU
#error DEFINE F_CPU FIRST
#endif 

/** \def WAIT
 * These are wait instructions for the transfer loop. They are strongly 
 * dependent on the frequency of the microcontroller's operation, therefore 
 * they are determined on its basis.
 */
#if F_CPU == 8000000
#define WAIT "nop\r\n"
#elif F_CPU == 16000000
#define WAIT "nop\r\nnop\r\nnop\r\nnop\r\n"
#else
#error NOT SUPPORTED FREQUENCY
#endif

/** \fn __ws2812b_send_byte
 * This function send one byte to stripe.
 * @pin Pin number to sending on
 * @data Data to send
 */
static void __ws2812b_send_byte(uint8_t pin, uint8_t data) {
    volatile uint8_t *port = pin_get_register(pin, PORT);
    uint8_t mask = pin_get_mask(pin);

    *(port - 1) |= mask;

    asm volatile (
        /* Load byte count */
        "ldi    r16,    8           \r\n"
        "send_byte_main_loop:       \r\n"
        
        /* Set pin to high */
        "st     %a1,    %2          \r\n"
        WAIT
        
        /* If bit is low, then set low state, if not, then continue high */
        "sbrs   %0,     7           \r\n"
        "st     %a1,    %3          \r\n"
        "lsl    %0                  \r\n"
        WAIT
        
        /* Go to low */
        "st     %a1,    %3          \r\n"
        WAIT

        /* If byte is not send, go up */
        "dec    r16                 \r\n"
        "brne   send_byte_main_loop \r\n"

        : 
        : "d" (data), 
          "b" (port),
          "d" (*port | mask),
          "d" (*port & ~mask)
        : "r16"
    );
}

/** \fn ws2812b_sender 
 * This function is a data sender for ws2812b led strip. Set it as the sender 
 * if the tape in the project is ws2812b.
 * @pin Pin to send on
 * @color Color to send
 */
void ws2812b_sender(uint8_t pin, color_t color) {
    __ws2812b_send_byte(pin, color.green);
    __ws2812b_send_byte(pin, color.red);
    __ws2812b_send_byte(pin, color.blue);
}

#endif
