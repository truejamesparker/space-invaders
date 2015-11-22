#include "bleSM.h"

// ----------------------------------------------------------------------------

void bleSM_tick() {
	// receives data, if any, from the BLE
	ble_receive();

	// if there is data available, the ble_receive() method will
	// take the data on the UARTLite and put into a queue for
	// later consumption. You can read characters out of this queue
	// using the ble_read() command, which returns a single char.
}
