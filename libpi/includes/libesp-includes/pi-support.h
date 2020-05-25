#ifndef __PI_SUPPORT_H__
#define __PI__SUPPORT_H__
// these are the pi-specific includes we need.

#include <ctype.h>
#include "rpi.h"
#include "sw-uart-int.h"

#define snprintf snprintk
#define malloc kmalloc

typedef enum {
    HW_UART,
    SW_UART,
} esp_handle_type_t;

typedef struct {
    esp_handle_type_t type;
    my_sw_uart_t * sw_uart;
} esp_handle_t;

#endif
