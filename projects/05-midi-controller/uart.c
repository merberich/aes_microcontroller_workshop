
#include "uart.h"

#include <avr/io.h>
#include <stddef.h>
#include "bit_tools.h"

// note: this is a percentage of baud
// according to analysis here:
//   https://www.allaboutcircuits.com/technical-articles/the-uart-baud-rate-clock-how-accurate-does-it-need-to-be/
// max allowable error is 3.75%
#define UART_BAUD_TOLERANCE 3

bool _UART__checkBaudHigh(uint32_t ubrr, uint32_t baud, bool use2x) {
  return 100 * (F_CPU) >
    ((use2x ? 8 : 16) * (ubrr + 1)) * (100 * baud + baud * UART_BAUD_TOLERANCE);
}

bool _UART__checkBaudLow(uint32_t ubrr, uint32_t baud, bool use2x) {
  return 100 * (F_CPU) <
    ((use2x ? 8 : 16) * (ubrr + 1)) * (100 * baud - baud * UART_BAUD_TOLERANCE);
}

bool UART__configure(UART__Parity parity, bool extraStop, uint32_t baud) {
  if (parity >= UART_PARITY_MAX || baud >= F_CPU) {
    return false;
  }

  // Configure USART usage mode
  UCSR0C &= ~((1 << UMSEL00) | (1 << UMSEL01));  // Using async mode
  UCSR0C |= (parity & 0x3) << UPM00;  // Assign parity mode
  _BIT_UPDATE(UCSR0C, USBS0, extraStop);  // Assign usage of extra stop

  // Configure baud rate generation
  // @note see avr-libc's util/setbaud.h for the calculation necessary
  uint32_t ubrr = ((F_CPU) + 8ul * baud) / (16ul * baud) - 1ul;
  bool use2x = false;
  if (_UART__checkBaudHigh(ubrr, baud, use2x)
      || _UART__checkBaudLow(ubrr, baud, use2x)) {
    use2x = true;
  }
  if (use2x) {
    // recalculate proposed ubrr to account for 2x async clock
    ubrr = ((F_CPU) + 4ul * baud) / (8ul * baud) - 1ul;
    if (_UART__checkBaudHigh(ubrr, baud, use2x)
        || _UART__checkBaudLow(ubrr, baud, use2x)) {
      return false;
    }
  }

  // Assign baud registers for successful baud rate assignment
  if (use2x) {
    _BIT_SET(UCSR0A, U2X0);
  }
  UBRR0L = ubrr & 0xFF;
  UBRR0H = ubrr >> 8;

  return true;
}

void UART__enable(void) {
  _BIT_SET(UCSR0B, TXEN0);
  _BIT_SET(UCSR0B, RXEN0);
}


void UART__disable(void) {
  _BIT_CLEAR(UCSR0B, TXEN0);
  _BIT_CLEAR(UCSR0B, RXEN0);
}

bool UART__transmit(uint8_t dataByte) {
  if (UART__txStatus() == UART_TXSTAT_NONE) {
    return false;
  }
  UDR0 = dataByte;  // Buffer the data byte
  return true;
}

UART__TxStatus UART__txStatus(void) {
  return _BIT_CHECK(UCSR0A, UDRE0) ? UART_TXSTAT_READY : UART_TXSTAT_NONE;
}

bool UART__receive(uint8_t* dataByte) {
  if (UART__rxStatus() == UART_RXSTAT_NONE || dataByte == NULL) {
    return false;
  }
  *dataByte = UDR0;  // Copy from the receive buffer
  return true;
}

UART__RxStatus UART__rxStatus(void) {
  uint8_t ucsr0a = UCSR0A;
  if (_BIT_CHECK(ucsr0a, RXC0)) {
    if (_BIT_CHECK(ucsr0a, FE0)) {
      return UART_RXSTAT_FRAME_ERR;
    }
    if (_BIT_CHECK(ucsr0a, DOR0)) {
      return UART_RXSTAT_OVER_ERR;
    }
    if (_BIT_CHECK(ucsr0a, UPE0)) {
      return UART_RXSTAT_PARITY_ERR;
    }
    return UART_RXSTAT_READY;  // byte is ready and valid
  }
  return UART_RXSTAT_NONE;
}
