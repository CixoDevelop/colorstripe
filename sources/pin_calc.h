#ifndef PIN_CALC_H_INCLUDED
#define PIN_CALC_H_INCLUDED

#ifdef __AVR_ARCH__

#include <avr/io.h>

/** \def AVR_CALC_PIN_NUMBER
 * This macro is used to calculate pin offset on AVR microcontrollers.
 */
#ifdef PORTA
#define AVR_CALC_PIN_NUMBER(X, Y) ((((X)) - &PORTA) * 3 + ((Y)))
#else
#define AVR_CALC_PIN_NUMBER(X, Y) ((((X)) - &PORTB) * 3 + ((Y)))
#endif

#endif

#endif
