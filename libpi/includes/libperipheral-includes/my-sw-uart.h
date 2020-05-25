// engler, cs140e: software uart interface.  the extra routines are mainly for 
// trying to read input fast enough without interrupts.
#ifndef __MY_SW_UART_H__
#define __MY_SW_UART_H__

#include "rpi.h"

// simple structure for sw-uart.  you'll likely have to extend in the future.
//  - rx: the GPIO pin used for receiving.  (make sure you set as input!)
//  - tx: the GPIO pin used for transmitting.  (make sure you set as output!)
//  - the baud rate: initially 115200, identical to what we already use.  if you
//      change this, you will also have to change the baud rate in pi-cat!
//  - cycle_per_bit: the number of cycles we have to hold the TX low (0) or 
//    high (1) to transmit a bit.  or, conversely, the number of cycles the 
//    RX pin will be held low or high by the sender.
typedef struct {
    uint8_t tx,rx;
    uint32_t baud;
    uint32_t cycle_per_bit;  // usec we send each bit.
} my_sw_uart_t;


// we inline compute usec_per_bit b/c we don't have division on the pi.  division
// by a constant allows the compiler to pre-compute.
#define my_sw_uart_init(_tx,_rx,_baud) \
    my_sw_uart_init_helper(_tx,_rx, _baud, (700*1000*1000UL)/_baud)
my_sw_uart_t my_sw_uart_init_helper(uint8_t tx, uint8_t rx, uint32_t baud, uint32_t cyc_per_bit);

int sw_uart_put8(my_sw_uart_t *uart, uint8_t b);

int sw_uart_get8(my_sw_uart_t *uart);

int sw_uart_put32(my_sw_uart_t *uart, uint32_t data);

uint32_t sw_uart_get32(my_sw_uart_t *uart);

#endif
