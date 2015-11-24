#include "controllerSM.h"

// allow for variable processing speeds (accelerometer tilt)
volatile static uint32_t processSMPeriods = 0;

// how fast should the tank be moving (accelerometer tilt)
volatile static uint32_t tankSpeed = CONTROLLER_TANK_MOVE_REGULAR;

// don't allow controller to process data sometimes
volatile static bool locked;

// ----------------------------------------------------------------------------

void controllerSM_tick() {
	// bail if this SM is locked
	if (locked) return;

	// It's been another SM period
	processSMPeriods++;

	if (processSMPeriods >= tankSpeed) {
		controller_process();

		// reset the period timer
		processSMPeriods = 0;
	}
}

// ----------------------------------------------------------------------------

void controllerSM_lock() {
	locked = true;
}

// ----------------------------------------------------------------------------

void controllerSM_unlock() {
	locked = false;
}

// ----------------------------------------------------------------------------

void controllerSM_updateTankSpeed(uint8_t speed) {
	tankSpeed = speed;
}

// ----------------------------------------------------------------------------
