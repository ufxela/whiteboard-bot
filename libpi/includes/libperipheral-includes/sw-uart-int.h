#ifndef __SW_UART_INT_H__
#define __SW_UART_INT_H__

#include "my-sw-uart.h"

// call this to enable my_sw_uart_t uart to be able to use the 
// interrupt based get8. 
// note: must have already called my_sw_uart_init to initialize uart.
// returns -1 on failure
int sw_uart_int_init(my_sw_uart_t * uart);

// interrupt based get8. Non blocking, returns -1 if no data
// otherwise, returns a byte of data
// internally stores reads in a queue so that we don't miss reads.
// note: currently, the first byte that we read is always an extra zero (b/c of some 1-0 transition?)
// and the last byte we read is currently an extra 0.
// but no data is lost--it's just sandwiched in between
int sw_uart_get8_int(my_sw_uart_t * uart);

// returns immediately (enqueues data into an internal queue)
int sw_uart_put8_int(my_sw_uart_t * uart, uint8_t data);

// clears the queue; resets in case of a mismatch/offset error
void sw_uart_int_reset(my_sw_uart_t * uart);

// 0 if no data, 1 if has data
int sw_uart_has_data_int(my_sw_uart_t * uart);

#endif