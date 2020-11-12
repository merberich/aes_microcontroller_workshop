
#include "adc.h"

#include <avr/io.h>
#include "bit_tools.h"

bool ADC__init(ADC_Vref vref, ADC_Prescaler presc) {
  if (vref >= ADC_VREF_MAX || presc >= ADC_PRESC_MAX) {
    return false;
  }

  ADCSRA = 0;  // Side effect: disables ADC while reconfiguring
  ADCSRA |= (presc & 0x07);  // Prescaler value (no shifting needed)

  ADMUX = 0;
  ADMUX |= ((vref & 0x03) << REFS0);  // Voltage reference
  _BIT_SET(ADMUX, ADLAR);  // Left-align output in ADCH/L (for 8-bit output)

  // Enable the ADC
  _BIT_SET(ADCSRA, ADEN);

  // Perform one full conversion for ADC initialization to finish
  ADC__startConversion(ADC_CHAN_GND);
  while (ADC__isConversionActive());

  return true;
}

bool ADC__isInitialized(void) {
  return _BIT_CHECK(ADCSRA, ADEN);
}

bool ADC__startConversion(ADC_ChannelSelect chan) {
  if (chan >= ADC_CHAN_MAX || ADC__isConversionActive() || !ADC__isInitialized()) {
    return false;
  }

  DIDR0 = 0;  // Clear any previous digital input disable
  if (chan <= ADC_CHAN_ADC5_PC5) {
    _BIT_SET(DIDR0, chan);  // Use less power on the specified ADC pin
  }

  ADMUX &= 0xF0;  // Clear MUXx bits
  ADMUX |= (chan & 0x0F);  // Assign new channel
  _BIT_SET(ADCSRA, ADSC);  // Kick off the conversion
  return true;
}

bool ADC__isConversionActive(void) {
  return _BIT_CHECK(ADCSRA, ADSC);
}

uint8_t ADC__getLastResult(void) {
  return ADCH;
}
