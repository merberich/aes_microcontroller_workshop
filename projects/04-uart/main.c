
#include "uart.h"
#include "gpio.h"

#include <util/delay.h>
#include <string.h>
#include <stddef.h>

//! Arduino LED maps to pin B5 (on when B5 is high).

#define LED_PIN GPIO_PB5
#define BAUD 115200

void writeString(char* str) {
  size_t len = strlen(str);
  for (size_t i = 0; i < len; ++i) {
    while (UART__txStatus() != UART_TXSTAT_READY);
    UART__transmit(str[i]);
  }
}

char readChar(void) {
  while (UART__rxStatus() != UART_RXSTAT_READY);
  uint8_t dataByte;
  UART__receive(&dataByte);
  return (char)dataByte;
}

int main(void) {
  GPIO__setLevel(LED_PIN, false);
  GPIO__setDirection(LED_PIN, GPIO_PINDIR_OUTPUT);

  bool res = UART__configure(UART_PARITY_NONE, false, BAUD);
  if (!res) {
    // signal error configuring UART
    GPIO__setLevel(LED_PIN, true);
    while (1);
  }
  UART__enable();

  while (1) {
    char in = readChar();
    if (in == 'a') {
      writeString("Hello World!\r\n");
    }
    else if (in == 'b') {
      writeString("More text...\r\n");
    }
    else {
      writeString("Invalid character.\r\n");
    }
  }
}
