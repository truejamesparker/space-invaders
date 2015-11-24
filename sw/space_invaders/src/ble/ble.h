#ifndef BLE_H
#define BLE_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "xparameters.h"
#include "xstatus.h"
#include "xuartlite.h"

#include "../queue/queue.h"

#define BLE_UART_DEVICE_ID		XPAR_AXI_UARTLITE_0_DEVICE_ID
#define BLE_UART_BUFF_SIZE		16 // UARTLite's max recv FIFO size
#define BLE_QUEUE_LENGTH		128

void ble_init();
void ble_send(char* msg, uint32_t length);
bool ble_available();
char ble_read();

#endif /* BLE_H */
