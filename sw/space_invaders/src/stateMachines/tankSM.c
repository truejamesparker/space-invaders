#include "tankSM.h"

// ----------------------------------------------------------------------------

void tankSM_init() {

}

// ----------------------------------------------------------------------------

void tankSM_tick() {
	// Tank direction
	if (pushButtons_leftPressed()) {
		tank_left();
	} else if (pushButtons_rightPressed()) {
		tank_right();
	}

	// Tank shooting
	if (pushButtons_centerPressed()) {
		missiles_tankFire();
	}
}

// ----------------------------------------------------------------------------
