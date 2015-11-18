#include "BLE.h"

static XUartLite UART;

static uint8_t sendBuffer[BLE_UART_BUFF_SIZE];
static uint8_t recvBuffer[BLE_UART_BUFF_SIZE];

void clearSendBuffer();
void clearRecvBuffer();
void clearBuffer(uint8_t *buffer, uint32_t length);
// ----------------------------------------------------------------------------

void ble_init() {
	// initialize our UART Lite
	XUartLite_Initialize(&UART, BLE_UART_DEVICE_ID);

	// clear my buffers
	clearSendBuffer();
	clearRecvBuffer();
}

// ----------------------------------------------------------------------------

void ble_send(char* msg, uint32_t length) {
	// Make sure that we only write as much as we are able
	if (length > BLE_UART_BUFF_SIZE) length = BLE_UART_BUFF_SIZE;

	// Do a deep copy and stage the msg to be sent into the buffer
	uint32_t i = 0;
    for (i=0; i<length; i++) sendBuffer[i] = msg[i];

    // TODO: some error checking, i.e., make sure what was sent was
    //       as long as what should have been sent.
    uint32_t sentBytes = XUartLite_Send(&UART, sendBuffer, BLE_UART_BUFF_SIZE);

	// do we actually need this?
    while (XUartLite_IsSending(&UART));
}

// ----------------------------------------------------------------------------

bool ble_available() {
	uint32_t bytes = XUartLite_Recv(&UART, recvBuffer, BLE_UART_BUFF_SIZE);

	return (bytes) ? true : false;
}

// ----------------------------------------------------------------------------

void ble_read(char* msg, uint32_t length) {

	// TODO: Use a FIFO to store chars, then pop one char at a time?

	// Make sure that we only read as much as we are able
	if (length > BLE_UART_BUFF_SIZE) length = BLE_UART_BUFF_SIZE;

	// Do a deep copy from recvBuffer to msg
	uint32_t i = 0;
	for (i=0; i<length; i++) msg[i] = recvBuffer[i];

	// clear the recvBuffer
	clearRecvBuffer();
}

// ----------------------------------------------------------------------------
// Private Helper Methods
// ----------------------------------------------------------------------------

void clearSendBuffer() {
	clearBuffer(sendBuffer, BLE_UART_BUFF_SIZE);
}

// ----------------------------------------------------------------------------

void clearRecvBuffer() {
	clearBuffer(recvBuffer, BLE_UART_BUFF_SIZE);
}

// ----------------------------------------------------------------------------

void clearBuffer(uint8_t *buffer, uint32_t length) {
	while (length--) buffer[length] = 0;
}
