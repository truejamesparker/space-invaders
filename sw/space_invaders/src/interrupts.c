#include "interrupts.h"

// Main interrupt dispatcher that calls the user-defined handlers
void interrupt_handler_dispatcher(void* ptr);

// User-defined interrupt handlers
void (*interrupts_timer_handler)(void);

// ----------------------------------------------------------------------------

//void interrupts_init() {
//	microblaze_register_handler(interrupt_handler_dispatcher, NULL);
//	XIntc_EnableIntr(XPAR_INTC_0_BASEADDR,
//		(XPAR_FIT_TIMER_0_INTERRUPT_MASK | XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK));
//	XIntc_MasterEnable(XPAR_INTC_0_BASEADDR);
//	microblaze_enable_interrupts();
//}

void interrupts_init() {
	microblaze_register_handler(interrupt_handler_dispatcher, NULL);
	// Enable interrupts from FIT, GPIO block, and AC97
	XIntc_EnableIntr(XPAR_INTC_0_BASEADDR,
		(XPAR_FIT_TIMER_0_INTERRUPT_MASK | XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK
				| XPAR_AXI_AC97_0_INTERRUPT_MASK));
	XIntc_MasterEnable(XPAR_INTC_0_BASEADDR);

	microblaze_enable_interrupts();
}

// ----------------------------------------------------------------------------

void interrupts_register_handler(uint8_t type, void (*func)(void)) {
	// Based on the type, set the appropriate interrupt handler
	if (type == INTS_TIMER) interrupts_timer_handler = func;
}

void fifo_interrupt_handler() {
	uint32_t i = 0;

	while(i++ < MAX_FIFO_SAMPLES && !XAC97_isInFIFOFull(XPAR_AXI_AC97_0_BASEADDR)){
//		uint32_t soundData = getCurrentSample();
		uint32_t soundData = getMixedSample();
		uint32_t sample = soundData | (soundData<<16); // Shifting to put in Left and Right
		XAC97_mSetInFifoData(XPAR_AXI_AC97_0_BASEADDR, sample); // Writing to the FIFO
	}
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
	}else if (status & XPAR_AXI_AC97_0_INTERRUPT_MASK) {

		fifo_interrupt_handler();

		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_AXI_AC97_0_INTERRUPT_MASK);
	}
}
