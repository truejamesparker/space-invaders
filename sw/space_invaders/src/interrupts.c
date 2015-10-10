#include "interrupts.h"

// Main interrupt dispatcher that calls the user-defined handlers
void interrupt_handler_dispatcher(void* ptr);

// User-defined interrupt handlers
void (*interrupts_timer_handler)(void);

// ----------------------------------------------------------------------------

void interrupts_init() {
	microblaze_register_handler(interrupt_handler_dispatcher, NULL);
	XIntc_EnableIntr(XPAR_INTC_0_BASEADDR,
		(XPAR_FIT_TIMER_0_INTERRUPT_MASK | XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK));
	XIntc_MasterEnable(XPAR_INTC_0_BASEADDR);
	microblaze_enable_interrupts();
}

// ----------------------------------------------------------------------------

void interrupts_register_handler(uint8_t type, void (*func)(void)) {
	// Based on the type, set the appropriate interrupt handler
	if (type == INTS_TIMER) interrupts_timer_handler = func;
}

// ----------------------------------------------------------------------------
// Interrupt Dispatcher
// ----------------------------------------------------------------------------

void interrupt_handler_dispatcher(void* ptr) {
	// Ask the Interrupt Controller for a status of its interrupts
	uint32_t status = XIntc_GetIntrStatus(XPAR_INTC_0_BASEADDR);

	// Check what triggered the interrupt
	if (status & XPAR_FIT_TIMER_0_INTERRUPT_MASK) {
		// Let the timer know it got an interrupt!
		if (interrupts_timer_handler) interrupts_timer_handler();

		// Then acknowledge it so it can interrupt again
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_FIT_TIMER_0_INTERRUPT_MASK);
	}
}
