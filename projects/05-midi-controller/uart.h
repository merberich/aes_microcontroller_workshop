#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>

//! Listing of parity bit options.
typedef enum {
  UART_PARITY_NONE = 0x0,  //! No parity bit.
  UART_PARITY_EVEN = 0x2,  //! Parity bit will make entire transmission "even".
  UART_PARITY_ODD = 0x3,   //! Parity bit will make entire transmission "odd".
  UART_PARITY_MAX          //! Number of parity config options (invalid value).
} UART__Parity;

//! Listing of transmission status cases.
typedef enum {
  UART_TXSTAT_NONE,   //! Not ready to transmit.
  UART_TXSTAT_READY,  //! Ready to transmit.
  UART_TXSTAT_MAX     //! Number of TX status cases.
} UART__TxStatus;

//! Listing of receipt status cases.
typedef enum {
  UART_RXSTAT_NONE,        //! Has not received.
  UART_RXSTAT_READY,       //! Data received, ready for read.
  UART_RXSTAT_FRAME_ERR,   //! Frame error: stop bit was not logic high.
  UART_RXSTAT_PARITY_ERR,  //! Parity error: parity doesn't match.
  UART_RXSTAT_OVER_ERR,    //! Data overrun error: unread byte overwritten in buffer.
  UART_RXSTAT_MAX          //! Number of RX status cases.
} UART__RxStatus;

//! This driver assumes all frames carry 8 bits of data.

//! Configure this UART. Must be called for valid UART transfers.
//! If "extraStop" is set, two stop bits will be used.
//! This function will attempt to find an achievable baud rate within 2% of "baud".
//! Even divisions of CPU frequency are guaranteed to be supported exactly.
//! Return false if invalid parmeters given or baud tolerance unachievable.
bool UART__configure(UART__Parity parity, bool extraStop, uint32_t baud);

//! Enable UART transmissions.
void UART__enable(void);

//! Disable UART transmissions (allow GPIO to use the UART signal pins).
void UART__disable(void);

//! Buffer one data byte to send via the UART if it is ready to transmit.
//! (Check via UART__txStatus)
//! Return true if a byte was buffered.
bool UART__transmit(uint8_t dataByte);

//! Check if the UART is ready to transmit a new frame.
UART__TxStatus UART__txStatus(void);

//! Fetch one data byte from the buffer if the UART has received a frame.
//! (Check via UART__rxStatus)
//! Return true if a byte was read (regardless of data validity).
bool UART__receive(uint8_t* dataByte);

//! Check if the UARt has received a frame, and the frame validity.
UART__RxStatus UART__rxStatus(void);

#endif  // UART_H
