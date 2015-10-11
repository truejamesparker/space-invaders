#include <stdio.h>

#include "platform.h"

#include "elements/aliens.h"
#include "elements/bunkers.h"
#include "elements/tank.h"
#include "elements/gameScreen.h"
#include "uartControl/uartControl.h"
#include "screen/screen.h"
#include "interrupts.h"
#include "tasks/taskControl.h"
#include "gpio/pushButtons.h"

void application_loop();

// ----------------------------------------------------------------------------

int main() {
	/**********************************
	 * Initialization Section
	 *********************************/
	init_platform();
	interrupts_init();
	screen_init();
	screen_clear();

	pushButtons_init();

	taskControl_init();

	// elements
	gameScreen_init();
	aliens_init();
	bunkers_init();
	tank_init();
	missiles_init();

	// text
	text_print_init();

	/**********************************
	 * Interrupt Registration Section
	 *********************************/
#if !(USE_UART_CONTROL) || FORCE_INTERRUPT_CONTROL
	// Register the task controller to run every time FIT expires
	interrupts_register_handler(INTS_TIMER, taskControl_tick);
#endif

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
	// refresh the screen after everything has been initialized
	screen_refresh();

	// Tell stdin that it gets zero! none! (as far as buffering goes)
	setvbuf(stdin, NULL, _IONBF, 0);

	print("********* Welcome to Space Invaders! *********\n\r\r\n");

	while(1) {
#if USE_UART_CONTROL
		// blocking call: wait until a character is present
		char input = getchar();

		// Handle the UART control of game
		uartControl_handle(input);

		// sync the screen with the frame
		screen_refresh();
#endif
	}

}

// ----------------------------------------------------------------------------
