#include "interrupts.h"

// Main interrupt dispatcher that calls the user-defined handlers
void interrupt_handler_dispatcher(void* ptr);

// User-defined interrupt handlers
void (*interrupts_timer_handler)(void);
void (*interrupts_audio_handler)(void);
void (*interrupts_dma_handler)(void);

// ----------------------------------------------------------------------------

void interrupts_init() {
	microblaze_register_handler(interrupt_handler_dispatcher, NULL);
	// Enable interrupts from FIT, GPIO block, and AC97
//	XIntc_EnableIntr(XPAR_INTC_0_BASEADDR,
//		(XPAR_FIT_TIMER_0_INTERRUPT_MASK | XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK
//				| XPAR_AXI_AC97_0_INTERRUPT_MASK));

	// Enable interrupts from the PIT, GPIO block, and AC97
	XIntc_EnableIntr(XPAR_INTC_0_BASEADDR,
		(XPAR_PIT_0_MYINTERRUPT_MASK | XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK
				| XPAR_AXI_AC97_0_INTERRUPT_MASK));

	XAC97_mSetControl(XPAR_AXI_AC97_0_BASEADDR, AC97_ENABLE_IN_FIFO_INTERRUPT);
	XIntc_MasterEnable(XPAR_INTC_0_BASEADDR);

	pit_load_value(1000000);
	pit_enable_load();
	pit_enable_count();
	pit_enable_interrupts();

	microblaze_enable_interrupts();
}

// ----------------------------------------------------------------------------

void interrupts_register_handler(uint8_t type, void (*func)(void)) {
	// Based on the type, set the appropriate interrupt handler
	if      (type == INTS_TIMER) interrupts_timer_handler = func;
	else if (type == INTS_AUDIO) interrupts_audio_handler = func;
	else if (type == INTS_DMA)   interrupts_dma_handler = func;
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

	} else if (status & XPAR_PIT_0_MYINTERRUPT_MASK) {
		if (interrupts_timer_handler) interrupts_timer_handler();

		// Then acknowledge it so it can interrupt again
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_PIT_0_MYINTERRUPT_MASK);

	} else if (status & XPAR_AXI_AC97_0_INTERRUPT_MASK) {
		// Let the audio controller know we got an interrupt!
		if (interrupts_audio_handler) interrupts_audio_handler();

		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_AXI_AC97_0_INTERRUPT_MASK);
	} else if (status & 0/*XPAR_DMA_THING_BASEADDR*/) {
		if (interrupts_dma_handler) interrupts_dma_handler();

		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, 0/*XPAR_DMA_THING_BASEADDR*/);
	}
}
