#include "BLE.h"

static XUartLite UART;

static uint8_t sendBuffer[BLE_UART_BUFF_SIZE];

static queue_t recvQueue;

void clearSendBuffer();
void clearBuffer(uint8_t *buffer, uint32_t length);
// ----------------------------------------------------------------------------

void ble_init() {
	// initialize our UART Lite
	XUartLite_Initialize(&UART, BLE_UART_DEVICE_ID);

	// clear my buffers
	clearSendBuffer();

	// create a queue
	queue_init(&recvQueue, BLE_QUEUE_LENGTH);
}

// ----------------------------------------------------------------------------

void ble_send(char* msg, uint32_t length) {

	// this function is fully implemented yet
	return;


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
	// temporary buffer to get byteses from UARTLite
	uint8_t recvBuffer[BLE_UART_BUFF_SIZE];

	uint32_t bytes = XUartLite_Recv(&UART, recvBuffer, BLE_UART_BUFF_SIZE);

	if (bytes) { // I have something to put into the queue

		// add each byte to the queue, overwriting stale data if necessary
		uint32_t i = 0;
		for (i=0; i<bytes; i++) {
			queue_overwritePush(&recvQueue, recvBuffer[i]);
		}
	}

	// if the receive queue isn't empty, then data is available
	return !queue_empty(&recvQueue);
}

// ----------------------------------------------------------------------------

char ble_read() {

	// if there is something to read, pop it back!
	if (!queue_empty(&recvQueue)) {
		return queue_pop(&recvQueue);
	}

	// else, return NULL
	return 0;
}

// ----------------------------------------------------------------------------
// Private Helper Methods
// ----------------------------------------------------------------------------

void clearSendBuffer() {
	clearBuffer(sendBuffer, BLE_UART_BUFF_SIZE);
}

// ----------------------------------------------------------------------------

void clearBuffer(uint8_t *buffer, uint32_t length) {
	while (length--) buffer[length] = 0;
}
