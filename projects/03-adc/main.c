
#include "gpio.h"
#include "adc.h"

#include <util/delay.h>

//! Arduino LED maps to pin B5 (on when B5 is high).
//! ADC channel will read on pin C0.
//! Connecting ADC pin to 5V should turn LED on.
//! Connecting ADC ping to 3.3V or GND should turn LED off.
//! This shows different behavior than digital read, which would sense 3.3V as high.

#define LED_PIN GPIO_PB5
#define ADC_VREF ADC_VREF_AVCC
#define ADC_PRESC ADC_PRESC_128
#define ADC_CHAN ADC_CHAN_ADC0_PC0
#define ADC_THRESH 180  // mapping a voltage less than 5V but greater than 3.3V

int main(void) {
  GPIO__setLevel(LED_PIN, false);
  GPIO__setDirection(LED_PIN, GPIO_PINDIR_OUTPUT);

  bool res = ADC__init(ADC_VREF, ADC_PRESC);
  if (!res) {
    while (1) {
      _delay_ms(100);
      GPIO__toggle(LED_PIN);
    }
  }

  while (1) {
    // Perform an ADC conversion
    res = ADC__startConversion(ADC_CHAN);
    if (!res) {
      while (1) {
        _delay_ms(100);
        GPIO__toggle(LED_PIN);
      }
    }
    while (ADC__isConversionActive());

    // If the ADC value read is less than the threshold, turn off the LED
    bool level = (ADC__getLastResult() < ADC_THRESH) ? false : true;
    GPIO__setLevel(LED_PIN, level);
  }
}
