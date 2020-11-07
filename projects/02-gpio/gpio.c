
#include "gpio.h"

#include <avr/io.h>
#include <bit_tools.h>

void GPIO__setDirection(GPIO__Pin pin, GPIO_PinDirection pinDir) {
  if (pinDir >= GPIO_PINDIR_MAX || pin >= GPIO_P_MAX) {
    return;  // Invalid cases
  }

  int portNum = _PIN_TO_PORT_NUM(pin);
  int pinIndex = _PIN_TO_PIN_INDEX(pin);

  switch (portNum) {
    case 0:
      // note: DDRA not supported
      //_BIT_UPDATE(DDRA, pinIndex, pinDir);
      break;
    case 1:
      _BIT_UPDATE(DDRB, pinIndex, pinDir);
      break;
    case 2:
      _BIT_UPDATE(DDRC, pinIndex, pinDir);
      break;
    case 3:
      _BIT_UPDATE(DDRD, pinIndex, pinDir);
      break;
    default:
      break;
  }
}

void GPIO_toggle(GPIO__Pin pin) {
  if (pin >= GPIO_P_MAX) {
    return;  // Invalid cases
  }

  int portNum = _PIN_TO_PORT_NUM(pin);
  int pinIndex = _PIN_TO_PIN_INDEX(pin);

  switch (portNum) {
    case 0:
      // note: PINA not supported
      //_BIT_SET(PINA, pinIndex);
      break;
    case 1:
      _BIT_SET(PINB, pinIndex);
      break;
    case 2:
      _BIT_SET(PINC, pinIndex);
      break;
    case 3:
      _BIT_SET(PIND, pinIndex);
      break;
    default:
      break;
  }
}

bool GPIO_getLevel(GPIO__Pin pin) {
  if (pin >= GPIO_P_MAX) {
    return false;  // Invalid cases
  }

  int portNum = _PIN_TO_PORT_NUM(pin);
  int pinIndex = _PIN_TO_PIN_INDEX(pin);

  switch (portNum) {
    case 0:
      // note: PINA not supported
      //return PINA & _BIT_VAL(pinIndex);
      return false;
    case 1:
      return PINB & _BIT_VAL(pinIndex);
    case 2:
      return PINC & _BIT_VAL(pinIndex);
    case 3:
      return PIND & _BIT_VAL(pinIndex);
    default:
      return false;
  }
}

void GPIO_setLevel(GPIO__Pin pin, bool level) {
  if (pin >= GPIO_P_MAX) {
    return;  // Invalid cases
  }

  int portNum = _PIN_TO_PORT_NUM(pin);
  int pinIndex = _PIN_TO_PIN_INDEX(pin);

  switch (portNum) {
    case 0:
      // note: PORTA not supported
      //_BIT_UPDATE(PORTA, pinIndex, level);
      break;
    case 1:
      _BIT_UPDATE(PORTB, pinIndex, level);
      break;
    case 2:
      _BIT_UPDATE(PORTC, pinIndex, level);
      break;
    case 3:
      _BIT_UPDATE(PORTD, pinIndex, level);
      break;
    default:
      break;
  }
}
