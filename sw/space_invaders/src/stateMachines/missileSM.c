#include "missileSM.h"

// alien and tank missiles are updated independently
volatile static uint32_t alienMissileSMPeriods = 0;
volatile static uint32_t tankMissileSMPeriods = 0;

// ----------------------------------------------------------------------------

void missileSM_tick() {
	// update periods
	alienMissileSMPeriods++;
	tankMissileSMPeriods++;

	// Tell the missiles to update.
	// We don't need to worry ourselves too much with optimization here
	// because inside this function, only active missiles are updated
	if (alienMissileSMPeriods == MISSILE_ALIEN_REFRESH) {
		missiles_moveAlienMissiles();

		// reset timer
		alienMissileSMPeriods = 0;
	}

	if (tankMissileSMPeriods == MISSILE_TANK_REFRESH) {
		missiles_moveTankMissile();

		// reset timer
		tankMissileSMPeriods = 0;
	}
}

// ----------------------------------------------------------------------------
