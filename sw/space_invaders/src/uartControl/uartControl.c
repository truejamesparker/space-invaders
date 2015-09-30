#include "uartControl.h"

uint16_t getint();

// ----------------------------------------------------------------------------

void uartControl_handle(char key) {

//	xil_printf("\b\r");

	switch(key) {
		/* Tank Controls */
		case '4': // left
			xil_printf("tank left\r\n");
			tank_left();
			break;
		case '6': // right
			xil_printf("tank left\r\n");
			tank_right();
			break;
		case '5': // shoot
			xil_printf("tank shoot\r\n");
			missiles_tank_fire();
			break;


		/* Alien Controls */
		case '8': // move
			xil_printf("alien move\r\n");
			aliens_march();
			break;
		case '1': // move n times
			xil_printf("How many times should I move alien? ");
			uint16_t n = getint();
			for (n; n > 0; n--) aliens_march();
			break;
		case '2': // kill
			xil_printf("Which alien should I kill? (0-54): ");

			// Get an int from the user
			uint16_t alien = getint();

			// Make sure it's within the bounds (0-54)
			if (alien >= ALIEN_LOW_COORDINATE && alien <= ALIEN_HIGH_COORDINATE){
				aliens_kill(alien);
				xil_printf(". bam!\n\r");
			} else {
				xil_printf(" Bailing.\r\n");
			}
			break;
		case '3': // shoot
			xil_printf("alien shoot\r\n");
			break;


		/* Update All Bullets */
		case '9':
			xil_printf("update all bullets\r\n");
			break;


		/* Erode Bunker */
		case '7': // query 0-3
			xil_printf("Which bunker should I erode? (0-3): ");
			uint16_t bunker = getint(); // query for the bunker
			if (bunker >= 0 && bunker <= 3) {
				xil_printf("%c. Okay, will do.\r\n", bunker);
				bunkers_damage(bunker);
			} else {
				xil_printf(" Bailing.\r\n");
			}
			break;


		default:
			break;
	}
}

//-----------------------------------------------------------------------------
// Private Helper Methods
//-----------------------------------------------------------------------------

#define INT_BUFFER_LENGTH 5
uint16_t getint() {
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
