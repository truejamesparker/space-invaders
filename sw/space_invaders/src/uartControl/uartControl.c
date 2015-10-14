#include "uartControl.h"

// for debugging
static uint8_t lives;
static uint32_t score;

static uint16_t getint();

// ----------------------------------------------------------------------------

void uartControl_handle(char key) {

	uint8_t i = 0;
	uint32_t j = 0;

	switch(key) {
		/* Tank Controls */
		case '4': // left
			xil_printf("tank left\r\n");
			tank_left();
			break;
		case '6': // right
			xil_printf("tank right\r\n");
			tank_right();
			break;
		case '5': // shoot
			xil_printf("tank shoot\r\n");
			missiles_tankFire();
			break;


		/* Alien Controls */
		case '8': // move
			xil_printf("alien move\r\n");
			aliens_march();
			break;
		case '1': // move n times
			xil_printf("How many times should I move alien? ");
			uint16_t n = getint();
			xil_printf("\r\n");
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
			uint16_t Xs[ALIEN_COL_COUNT];
			uint16_t Ys[ALIEN_COL_COUNT];
			aliens_getLowestAliens(Xs, Ys);
			uint16_t x = (rand()%ALIEN_COL_COUNT);
			missiles_alienFire(Xs[x], Ys[x]);
			break;


		/* Update All Bullets */
		case '9':
			xil_printf("update all bullets\r\n");
			missiles_move();
			break;


		/* Erode Bunker */
		case '7': // query 0-3
			xil_printf("Which bunker should I erode? (0-3): ");
			uint16_t bunker = getint(); // query for the bunker
			if (bunker >= 0 && bunker <= 3) {
				xil_printf("%c. Okay, will do.\r\n", bunker);
//				bunkers_damage(bunker);
			} else {
				xil_printf(" Bailing.\r\n");
			}
			break;

		/* Miscellaneous Scaling */
		case 'a':
			aliens_left();
			break;
		case 'A':
			aliens_up();
			break;
		case 's':
			aliens_right();
			break;
		case 'S':
			aliens_down();
			break;
		case 'c':
			screen_clear();
			gameScreen_init();
			aliens_init();
			tank_init();
			missiles_init();
			bunkers_init();
			break;

		case '/':
			lives = gameScreen_increaseLives(-1);
			xil_printf("Setting lives: %d\r\n", lives);
			break;

		case '*':
			lives = gameScreen_increaseLives(1);
			xil_printf("Setting lives: %d\r\n", lives);
			break;

		case '-':
			score = gameScreen_increaseScore(-1);
			xil_printf("Setting score: %d\r\n", score);
			break;

		case '+':
			score = gameScreen_increaseScore(1);
			xil_printf("Setting score: %d\r\n", score);
			break;

		case '.':
			spaceship_start();
			break;

		case 'l':
			xil_printf("Here are the lowest living aliens:\r\n");
			uint16_t xs[ALIEN_COL_COUNT] = { 0 };
			uint16_t ys[ALIEN_COL_COUNT] = { 0 };
			aliens_getLowestAliens(xs, ys);

			for (i=0; i<ALIEN_COL_COUNT; i++) {
				xil_printf("Lowest Alien: (%d, %d)\r\n", xs[i], ys[i]);
			}

			break;

		case 'k':
			xil_printf("Killing almost all aliens...\r\n");
			for (i=1; i<ALIEN_COUNT-3; i++) {
				aliens_kill(i);
				j = 100000000;
				while(--j);
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
static uint16_t getint() {
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
