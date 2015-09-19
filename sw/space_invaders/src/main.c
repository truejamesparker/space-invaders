#include <stdio.h>

#include "platform.h"

#include "uartControl/uartControl.h"

void print(char *str);

void application_loop();

// ----------------------------------------------------------------------------

int main() {
	/**********************************
	 * Initialization Section
	 *********************************/
	init_platform();

	print("Hello World\n\r");

	/**********************************
	 * Main Application Loop
	 *********************************/
	application_loop();



	// The code should never get here.
	cleanup_platform();
	return 0;
}

// ----------------------------------------------------------------------------

void application_loop() {
	char input;

	//	setvbuf(stdin, NULL, _IONBF, 0);

	while(1) {
		// blocking call: wait until a character is present
		input = getchar();

		// Handle the UART control of game
		uartControl_handle(input);
	}

}
