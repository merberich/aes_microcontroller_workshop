#ifndef BIT_TOOLS_H
#define BIT_TOOLS_H

//! Macro: get value of bit at position "bit".
#define _BIT_VAL(bit)  (1 << bit)

//! Macro: set bit in position "bit" within "dst".
#define _BIT_SET(dst, bit) (dst |= (_BIT_VAL(bit)))

//! Macro: clear bit in position "bit" within "dst".
#define _BIT_CLEAR(dst, bit) (dst &= ~(_BIT_VAL(bit)))

//! Macro: assign bit position "bit" within "dst" to truth value "val".
#define _BIT_UPDATE(dst, bit, val) (val ? _BIT_SET(dst, bit) : _BIT_CLEAR(dst, bit))

//! Macro: check logical value of bit position "bit" within "src".
#define _BIT_CHECK(src, bit) (src & _BIT_VAL(bit))

//! Macro: convert a pin number to its associated port number.
#define _PIN_TO_PORT_NUM(pin) (pin >> 3)  // Divide by 8 to identify port number

//! Macro: convert pin number to its index in register.
#define _PIN_TO_PIN_INDEX(pin) (pin & 0x07)

#endif  // BIT_TOOLS_H
