#ifndef ADC_H
#define ADC_H

#include <stdbool.h>
#include <stdint.h>

//! Listing of all voltage references supported.
typedef enum {
  ADC_VREF_AREF = 0x0,       //! Using external AREF pin as voltage reference.
  ADC_VREF_AVCC = 0x1,       //! Using AVCC (VCC) as voltage reference.
  ADC_VREF_INTERNAL = 0x3,   //! Using 1.1V internal ADC voltage reference.
  ADC_VREF_MAX               //! Number of voltage reference options (invalid value).
} ADC_Vref;

//! Listing of all valid ADC input channel configurations.
typedef enum {
  ADC_CHAN_ADC0_PC0 = 0x0,  //! ADC0 pin (PC0).
  ADC_CHAN_ADC1_PC1 = 0x1,  //! ADC1 pin (PC1).
  ADC_CHAN_ADC2_PC2 = 0x2,  //! ADC2 pin (PC2).
  ADC_CHAN_ADC3_PC3 = 0x3,  //! ADC3 pin (PC3).
  ADC_CHAN_ADC4_PC4 = 0x4,  //! ADC4 pin (PC4).
  ADC_CHAN_ADC5_PC5 = 0x5,  //! ADC5 pin (PC5).
  ADC_CHAN_TEMP = 0x8,      //! Internal temperature sensor channel.
  ADC_CHAN_INTERNAL = 0xE,  //! Channel connected to 1.1V internal reference.
  ADC_CHAN_GND = 0xF,       //! Channel connected directly to ground net.
  ADC_CHAN_MAX              //! Highest number of channel options (invalid value).
} ADC_ChannelSelect;

//! Listing possible prescalers for ADC clock.
typedef enum {
  ADC_PRESC_DEFAULT,  //! Default value is division by 2.
  ADC_PRESC_2,
  ADC_PRESC_4,
  ADC_PRESC_8,
  ADC_PRESC_16,
  ADC_PRESC_32,
  ADC_PRESC_64,
  ADC_PRESC_128,
  ADC_PRESC_MAX  //! Number of prescaler options (invalid value).
} ADC_Prescaler;

//! Initialize this ADC driver. Must be called before any other ADC driver function.
//! Assign voltage refrence and prescaler before initializing.
//! Return false if voltage reference or prescaler arguments are invalid.
bool ADC__init(ADC_Vref vref, ADC_Prescaler presc);

//! Return true if this ADC has been initialized.
bool ADC__isInitialized(void);

//! Begin an ADC conversion on the specified channel.
//! Returns false if not initialized, channel is invalid, or conversion active.
bool ADC__startConversion(ADC_ChannelSelect chan);

//! Returns true if a conversion is still active. False on complete or no conversion.
bool ADC__isConversionActive(void);

//! Returns 8-bit value last read by the ADC.
//! Mapping: (0V) => 0, (VREF - 1 LSB) => 255.
uint8_t ADC__getLastResult(void);

#endif  // ADC_H
