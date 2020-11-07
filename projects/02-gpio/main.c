
#include "gpio.h"

//! Arduino LED maps to pin B5 (on when B5 is high).
//! Our input pin will be pin B4 (Arduino "Digital pin" 12).
//! Connect VCC to Arduino pin 12 via jumper to have LED light up.

#define LED_PIN GPIO_PB5
#define INPUT_PIN GPIO_PB4

int main(void) {
  GPIO_setLevel(LED_PIN, false);
  GPIO__setDirection(LED_PIN, GPIO_PINDIR_OUTPUT);

  GPIO_setLevel(INPUT_PIN, false);
  GPIO__setDirection(INPUT_PIN, GPIO_PINDIR_INPUT);

  while (1) {
    GPIO_setLevel(LED_PIN, GPIO_getLevel(INPUT_PIN));
  }
}
