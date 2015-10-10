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

bool pushButtons_LeftPressed() {
	return XGpio_DiscreteRead(&gpPB, CH) & BTN_LEFT_MASK;
}

// ----------------------------------------------------------------------------

bool pushButtons_RightPressed() {
	return XGpio_DiscreteRead(&gpPB, CH) & BTN_RIGHT_MASK;
}

// ----------------------------------------------------------------------------

bool pushButtons_DownPressed() {
	return XGpio_DiscreteRead(&gpPB, CH) & BTN_DOWN_MASK;
}

// ----------------------------------------------------------------------------

bool pushButtons_UpPressed() {
	return XGpio_DiscreteRead(&gpPB, CH) & BTN_UP_MASK;
}

// ----------------------------------------------------------------------------

bool pushButtons_CenterPressed() {
	return XGpio_DiscreteRead(&gpPB, CH) & BTN_CENTER_MASK;
}

// ----------------------------------------------------------------------------
