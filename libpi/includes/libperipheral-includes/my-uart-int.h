#ifndef __MY_UART_INT_H__
#define __MY_UART_INT_H__
#include "uart.h"

typedef enum { MY_UART_NO_INT = 0, MY_UART_TX_INT = 1111, MY_UART_RX_INT = 2222 } my_uart_int_t;

typedef struct aux_periphs hw_my_uart_t;

// has to be called last!   make sure you don't do a subsequent my_uart_init()
void my_uart_init_with_interrupts(void);

my_uart_int_t my_uart_has_int(hw_my_uart_t *uart);
void my_uart_clear_int(hw_my_uart_t *uart);

unsigned *const my_uart_get_aux_irq(void) ;

int my_uart_getc_int(void);
int my_uart_putc_int(int c);
// int my_uart_putc_int(uint8_t c);
void my_uart_int_attach_handler(void);

extern volatile unsigned n_my_uart_interrupts;

int my_uart_has_data_int(void);

// flush all of the interrupt put Q to the UART.  interrupts must
// be disabled.
void my_uart_int_flush_all(void);


#endif
