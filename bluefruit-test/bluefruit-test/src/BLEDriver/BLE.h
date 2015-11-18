#ifndef BLE_H
#define BLE_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "xparameters.h"
#include "xstatus.h"
#include "xuartlite.h"

#define BLE_UART_DEVICE_ID		XPAR_AXI_UARTLITE_0_DEVICE_ID
#define BLE_UART_BUFF_SIZE		16 // UARTLite's max recv FIFO size

void ble_init();
void ble_send(char* msg, uint32_t length);
bool ble_available();
void ble_read(char* msg, uint32_t length);

#endif /* BLE_H */
