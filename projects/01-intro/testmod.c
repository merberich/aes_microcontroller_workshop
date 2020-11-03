#include "testmod.h"

#include <avr/io.h>

void configurePortB(void) {
  DDRB = 0xFF;
  PORTB = 0xAA;
}

void togglePortB(void) {
  PORTB ^= 0xAA;
}
