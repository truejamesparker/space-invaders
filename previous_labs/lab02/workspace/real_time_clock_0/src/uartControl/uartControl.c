#include "uartControl.h"

static uint32_t getint();


// ----------------------------------------------------------------------------

void uartControl_handle(char key) {

	switch(key) {
		case 'l': // load
			pit_disable_count();
			xil_printf("\n\r\n\rLoad value: ");

			// Get an int from the user
			int32_t value = getint();

			// Make sure it's within the bounds (0-10s)
			if (value >= 0 && value <= 4000000000){
				pit_load_value(value);
				xil_printf("\n\r\n\rTimer updated!\n\r");
			} else {
				xil_printf("\n\r\n\rInvalid load value!\r\n");
			}
			pit_enable_count();
			break;

		default:
			break;
	}
}

//-----------------------------------------------------------------------------
// Private Helper Methods
//-----------------------------------------------------------------------------

#define INT_BUFFER_LENGTH 10
static uint32_t getint() {
	// +1 for the termination '\0'
	char buffer[INT_BUFFER_LENGTH+1];

	// Keep track of where to add the char in the buffer string
	uint16_t i = 0;

	char input = getchar();

	// If the input char isn't a return or newline and we
	// still have room in the buffer, ask for a new input!
	while (input != '\r' && input != '\n' && i<INT_BUFFER_LENGTH) {
		// Only add to the buffer if it's between 0 and 9.
		if (input >= ASCII_0 && input <= ASCII_9) {
			// print it out so it looks like we are typing
			xil_printf("%c", input);

			// Add to the buffer to run atoi() against later
			buffer[i] = input;

			i++;
		}

		// Get another character!
		input = getchar();
	}

	// Add the termination char for atoi()
	// Make sure that this is indexed at i so that
	// atoi() doesn't freak out.
	buffer[i] = '\0';

	// convert to int representation
	return atoi(buffer);
}

//-----------------------------------------------------------------------------
