#include "slideSwitches.h"

#define CH	1 // GPIO Channel 1

static XGpio gpSW;

// ----------------------------------------------------------------------------

void slideSwitches_init() {
	// Initialize the GPIO peripherals
	XGpio_Initialize(&gpSW, XPAR_SLIDE_SWTICHES_8BITS_DEVICE_ID);

	// Set the slide switch peripheral to be inputs
	// This is the last 8 (0xFF) bits
	XGpio_SetDataDirection(&gpSW, CH, 0x000000FF);
}

// ----------------------------------------------------------------------------

bool slideSwitches_isOn(uint8_t sw) {
	return XGpio_DiscreteRead(&gpSW, CH) & SW_CREATE_MASK(sw);
}

// ----------------------------------------------------------------------------
