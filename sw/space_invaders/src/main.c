#include <stdio.h>

#include "platform.h"

#include "elements/aliens.h"
#include "uartControl/uartControl.h"
#include "screen/screen.h"

void print(char *str);

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

	// refresh rate
	uint32_t sillyTimer = MAX_SILLY_TIMER;

	// Which alien we are on
	uint32_t alienCounter = 0;

	while(1) {

		// Wait until we are ready to refresh screen again
		while(sillyTimer--);
		sillyTimer = MAX_SILLY_TIMER;

		// ----------------
		// Do some screen stuff

		bool* lives = aliens_getLives();
		lives[alienCounter] = !lives[alienCounter];
		if (++alienCounter >= ALIEN_COUNT) alienCounter = 0;

		aliens_draw();

		screen_refresh();
		// ----------------

		/****
		 * To enable the UART controller, uncomment below
		 */

//		// blocking call: wait until a character is present
//		input = getchar();
//
//		// Handle the UART control of game
//		uartControl_handle(input);

	}

}
