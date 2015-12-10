#include "timer.h"

static XTmrCtr TmrCtrInstancePtr;
static bool initialized = false;
static bool started = false;

static uint32_t startTime = 0;
static uint32_t stopTime = 0;

// ----------------------------------------------------------------------------

void timer_init() {
	XTmrCtr_Initialize(&TmrCtrInstancePtr, XPAR_AXI_TIMER_0_DEVICE_ID);
	initialized = true;
}

// ----------------------------------------------------------------------------

void timer_start() {
	if (!initialized) return;
	started = true;

	XTmrCtr_Reset(&TmrCtrInstancePtr, 0);
	startTime = XTmrCtr_GetValue(&TmrCtrInstancePtr, 0);
	XTmrCtr_Start(&TmrCtrInstancePtr, 0);
}

// ----------------------------------------------------------------------------

void timer_stop(uint32_t *elapsedTime) {
	if (!initialized || !started) return;

	XTmrCtr_Stop(&TmrCtrInstancePtr, 0);
	stopTime = XTmrCtr_GetValue(&TmrCtrInstancePtr, 0);

	*elapsedTime = (stopTime - startTime);

	started = false;
}

// ----------------------------------------------------------------------------
