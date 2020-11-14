#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>

//! Listing of all pins available on the ATMega328p.
//! Some of these pins might not be configurable as GPIO.
//! See datasheet page 12 for reserved pins.
typedef enum {
  GPIO_PA0, GPIO_PA1, GPIO_PA2, GPIO_PA3, GPIO_PA4, GPIO_PA5, GPIO_PA6, GPIO_PA7,
  GPIO_PB0, GPIO_PB1, GPIO_PB2, GPIO_PB3, GPIO_PB4, GPIO_PB5, GPIO_PB6, GPIO_PB7,
  GPIO_PC0, GPIO_PC1, GPIO_PC2, GPIO_PC3, GPIO_PC4, GPIO_PC5, GPIO_PC6, GPIO_PC7,
  GPIO_PD0, GPIO_PD1, GPIO_PD2, GPIO_PD3, GPIO_PD4, GPIO_PD5, GPIO_PD6, GPIO_PD7,
  GPIO_P_MAX  //! Number of pins available (invalid value).
} GPIO__Pin;

//! Description of available states for GPIO pins.
typedef enum {
  GPIO_PINDIR_INPUT,
  GPIO_PINDIR_OUTPUT,
  GPIO_PINDIR_MAX  //! Number of directions (invalid value).
} GPIO__PinDirection;


//! Configure a pin with the specified pin direction.
void GPIO__setDirection(GPIO__Pin pin, GPIO__PinDirection pinDir);

//! For pins in output mode, toggle the logic level.
//! For pins in input mode, toggle between pull-up and high-impedance mode.
void GPIO__toggle(GPIO__Pin pin);

//! Get the current logic level for a specific pin.
bool GPIO__getLevel(GPIO__Pin pin);

//! For pins in output mode, set the logic level.
//! For pins in input mode, if level is true, enter pull-up mode; if false, enter high-impedance.
void GPIO__setLevel(GPIO__Pin pin, bool level);

#endif  // GPIO_H
