#include "missileSM.h"

// ----------------------------------------------------------------------------

void missileSM_tick() {
	// Tell the missiles to update.
	// We don't need to worry ourselves too much with optimization here
	// because inside this function, only active missiles are updated
	missiles_move();
}

// ----------------------------------------------------------------------------
