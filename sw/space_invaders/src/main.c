#include <stdio.h>

#include "platform.h"

#include "elements/aliens.h"
#include "elements/bunkers.h"
#include "uartControl/uartControl.h"
#include "screen/screen.h"
#include "elements/tank.h"

void application_loop();

// ----------------------------------------------------------------------------

int main() {
	/**********************************
	 * Initialization Section
	 *********************************/
	init_platform();
	screen_init();
	screen_clear();

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

#define MAX_SILLY_TIMER	1000000
void application_loop() {
	char input;

	aliens_init();
	bunkers_init_origins();
	tank_init();

	bunkers_draw();

	// refresh the screen after everything has been initialized
	screen_refresh();

	// Tell stdin that it gets zero! none! (as far as buffering goes)
	setvbuf(stdin, NULL, _IONBF, 0);

	while(1) {
		// blocking call: wait until a character is present
		input = getchar();

		// Handle the UART control of game
		uartControl_handle(input);

		// sync the screen with the frame
		screen_refresh();
	}

}
