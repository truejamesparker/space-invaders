#include "tankSM.h"

// ----------------------------------------------------------------------------

void tankSM_init() {

}

// ----------------------------------------------------------------------------

void tankSM_tick() {
	// Tank direction
	if (pushButtons_LeftPressed()) {
		tank_left();
	} else if (pushButtons_RightPressed()) {
		tank_right();
	}

	// Tank shooting
	if (pushButtons_CenterPressed()) {
		missiles_tank_fire();
	}
}

// ----------------------------------------------------------------------------
