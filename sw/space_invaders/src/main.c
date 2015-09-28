#include <stdio.h>

#include "platform.h"

#include "elements/aliens.h"
#include "elements/bunkers.h"
#include "uartControl/uartControl.h"
#include "screen/screen.h"
#include "elements/tank.h"

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
	bool up = true;

	aliens_init_rel_origins();
	aliens_init_lives_array();
	bunkers_init_origins();
	tank_init();

	bunkers_draw();
	aliens_draw();
	tank_draw();


//	int this = 0;
//	while(this<1000){
//		this++;
//		xil_printf("%d\n\r", this);
//	}


	setvbuf(stdin, NULL, _IONBF, 0);

	screen_refresh();
	char i;
	while(1) {\
		i = getchar();
		uartControl_handle(i);
//		// Wait until we are ready to refresh screen again
//		while(sillyTimer--);
//		sillyTimer = MAX_SILLY_TIMER;
//
//		// ----------------
//		// Do some screen stuff
//
////		bool* lives = aliens_getLives();
////		lives[alienCounter] = !lives[alienCounter];
////		if (++alienCounter >= ALIEN_COUNT) alienCounter = 0;
//
//		up = !up;
//		flapIn = up;
//		aliens_march_right();
////		aliens_march_down();
//		aliens_draw();
//		tank_draw();
		screen_refresh();


	}

}
