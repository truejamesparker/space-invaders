#include "pushButtons.h"

#define CH	1 // GPIO Channel 1

static XGpio gpPB;

// ----------------------------------------------------------------------------

void pushButtons_init() {
	// Initialize the GPIO peripherals
	XGpio_Initialize(&gpPB, XPAR_PUSH_BUTTONS_5BITS_DEVICE_ID);

	// Set the push button peripheral to be inputs
	// This is the last 5 (0x1F) bits
	XGpio_SetDataDirection(&gpPB, CH, 0x0000001F);
}

// ----------------------------------------------------------------------------

bool pushButtons_leftPressed() {
	return XGpio_DiscreteRead(&gpPB, CH) & BTN_LEFT_MASK;
}

// ----------------------------------------------------------------------------

bool pushButtons_rightPressed() {
	return XGpio_DiscreteRead(&gpPB, CH) & BTN_RIGHT_MASK;
}

// ----------------------------------------------------------------------------

bool pushButtons_downPressed() {
	return XGpio_DiscreteRead(&gpPB, CH) & BTN_DOWN_MASK;
}

// ----------------------------------------------------------------------------

bool pushButtons_upPressed() {
	return XGpio_DiscreteRead(&gpPB, CH) & BTN_UP_MASK;
}

// ----------------------------------------------------------------------------

bool pushButtons_centerPressed() {
	return XGpio_DiscreteRead(&gpPB, CH) & BTN_CENTER_MASK;
}

// ----------------------------------------------------------------------------

bool pushButtons_anyPressed() {
	return XGpio_DiscreteRead(&gpPB, CH) & BTN_ANY_MASK;
}

// ----------------------------------------------------------------------------
