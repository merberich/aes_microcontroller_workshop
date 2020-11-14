
#include "gpio.h"
#include "adc.h"
#include "uart.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// Hardware configuration
#define LED GPIO_PB5
#define BUTTON0 GPIO_PD7
#define BUTTON1 GPIO_PD6
#define BUTTON2 GPIO_PD5
#define BUTTON3 GPIO_PD4
#define KNOB ADC_CHAN_ADC0_PC0

// Software configuration
#define ADC_VREF ADC_VREF_AVCC
#define ADC_PRESC ADC_PRESC_128
#define UART_PARITY UART_PARITY_NONE
#define UART_STOP false
#define UART_BAUD 115200

#define MIDI_CHANNEL 0x01

#define MIDI_STAT_NOTE_OFF 0x80
#define MIDI_STAT_NOTE_ON 0x90
#define MIDI_STAT_CC 0xB0

#define MIDI_CC_MODWHEEL 0x01

typedef struct {
  bool button0;
  bool button1;
  bool button2;
  bool button3;
  uint8_t knob;
} ControlState;

void init(void) {
  // Configure LED
  GPIO__setLevel(LED, false);
  GPIO__setDirection(LED, GPIO_PINDIR_OUTPUT);

  // Configure buttons as high-impedance inputs
  GPIO__setLevel(BUTTON0, false);
  GPIO__setDirection(BUTTON0, GPIO_PINDIR_INPUT);
  GPIO__setLevel(BUTTON1, false);
  GPIO__setDirection(BUTTON1, GPIO_PINDIR_INPUT);
  GPIO__setLevel(BUTTON2, false);
  GPIO__setDirection(BUTTON2, GPIO_PINDIR_INPUT);
  GPIO__setLevel(BUTTON3, false);
  GPIO__setDirection(BUTTON3, GPIO_PINDIR_INPUT);

  // Configure ADC
  ADC__init(ADC_VREF, ADC_PRESC);

  // Configure UART
  UART__configure(UART_PARITY, UART_STOP, UART_BAUD);
  UART__enable();
}

void updateKnob(ControlState* ctlState) {
  ADC__startConversion(KNOB);
  while (ADC__isConversionActive());
  ctlState->knob = ADC__getLastResult();
}

void updateButtons(ControlState* ctlState) {
  ctlState->button0 = GPIO__getLevel(BUTTON0);
  ctlState->button1 = GPIO__getLevel(BUTTON1);
  ctlState->button2 = GPIO__getLevel(BUTTON2);
  ctlState->button3 = GPIO__getLevel(BUTTON3);
}

void sendMIDI(uint8_t status, uint8_t data0, uint8_t data1) {
  status |= MIDI_CHANNEL;  // channel is part of status byte
  while (UART__txStatus() != UART_TXSTAT_READY);
  UART__transmit(status);
  while (UART__txStatus() != UART_TXSTAT_READY);
  UART__transmit(data0);
  while (UART__txStatus() != UART_TXSTAT_READY);
  UART__transmit(data1);
}

void transmitDifferences(ControlState* last, ControlState* curr) {
  if (last->button0 != curr->button0) {
    sendMIDI(curr->button0 ? MIDI_STAT_NOTE_ON : MIDI_STAT_NOTE_OFF, 60, 0x7F);
  }
  if (last->button1 != curr->button1) {
    sendMIDI(curr->button1 ? MIDI_STAT_NOTE_ON : MIDI_STAT_NOTE_OFF, 62, 0x7F);
  }
  if (last->button2 != curr->button2) {
    sendMIDI(curr->button2 ? MIDI_STAT_NOTE_ON : MIDI_STAT_NOTE_OFF, 64, 0x7F);
  }
  if (last->button3 != curr->button3) {
    sendMIDI(curr->button3 ? MIDI_STAT_NOTE_ON : MIDI_STAT_NOTE_OFF, 65, 0x7F);
  }
  if (last->knob != curr->knob) {
    // note: this implements a dead zone for noise filtering
    sendMIDI(MIDI_STAT_CC, MIDI_CC_MODWHEEL, curr->knob / 2);
  }
}

int main(void) {
  ControlState currState, lastState;

  init();

  while (1) {
    memcpy(&lastState, &currState, sizeof(ControlState));
    updateKnob(&currState);
    updateButtons(&currState);
    transmitDifferences(&lastState, &currState);
  }
}
