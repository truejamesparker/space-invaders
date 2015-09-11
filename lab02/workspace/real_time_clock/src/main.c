#include <stdio.h>          // xil_printf and so forth.
#include <stdint.h>			// uint32_t and so forth.

#include "xgpio.h"          // Provides access to PB GPIO driver.
#include "platform.h"       // Enables caching and other system stuff.
#include "mb_interface.h"   // provides the microblaze interrupt enables, etc.
#include "xintc_l.h"        // Provides handy macros for the interrupt controller.

#include "clock/clock.h"
#include "debouncer/debouncer.h"

XGpio gpLED;  // This is a handle for the LED GPIO block.
XGpio gpPB;   // This is a handle for the push-button GPIO block.
u8 counter; // tens of milliseconds
char time[5] = "";
uint32_t oldButtonState = 0;

uint8_t debounceCounterEnabled = 0;
uint8_t debounceCounter = 0;

uint32_t oldState = 0;

// This is invoked in response to a timer interrupt.
// It does 2 things: 1) debounce switches, and 2) advances the time.
void timer_interrupt_handler() {
	// for testing only
	uint32_t seconds = 0;
	uint32_t minutes = 0;
	uint32_t hours = 0;

	if (++counter == 100){

		// clear the counter, it's been a second
		counter = 0;

		// increment the clock
		incrementClock();

		// For testing only.
		getClock(&seconds, &minutes, &hours);
//		xil_printf("\b\b\b\b\b\b\b\b%02d:%02d:%02d", hours, minutes, seconds);

	}

//	if(bounce_enabled()){
//		inc_bouncer();
//	}

	if (debounceCounterEnabled && ++debounceCounter == 5) {
		xil_printf("Debounced Button 1!\n");
		debounceCounter = 0;
		debounceCounterEnabled = 0;
	}

//	if (enabledBtn1 && ++btn1Count == 5) {
//		xil_printf("Debounced Button 1!\n");
//		btn1Count = 0;
//		enabledBtn1 = 0;
//	}
}

// This is invoked each time there is a change in the button state (result of a push or a bounce).
void pb_interrupt_handler() {
	// Clear the GPIO interrupt.
	XGpio_InterruptGlobalDisable(&gpPB);                // Turn off all PB interrupts for now.
	u32 currentButtonState = XGpio_DiscreteRead(&gpPB, 1);  // Get the current state of the buttons.
	//  xil_printf("push buttons: 0x%x\n", currentButtonState);
	// You need to do something here.

	if (currentButtonState != oldState) {
		debounceCounterEnabled = 1;
		debounceCounter = 0;
	} else {//if (debounceCounterEnabled) {
		debounceCounter = 0;
	}
//	if (currentButtonState & 0x01) { // btn 1 pressed
//		enabledBtn1 = 1;
//	} else {
//		enabledBtn1 = 0;
//		btn1Count = 0;
//	}


//	bouncer(currentButtonState);

	XGpio_InterruptClear(&gpPB, 0xFFFFFFFF);            // Ack the PB interrupt.
	XGpio_InterruptGlobalEnable(&gpPB);                 // Re-enable PB interrupts.
}

// Main interrupt handler, queries the interrupt controller to see what peripheral
// fired the interrupt and then dispatches the corresponding interrupt handler.
// This routine acks the interrupt at the controller level but the peripheral
// interrupt must be ack'd by the dispatched interrupt handler.
void interrupt_handler_dispatcher(void* ptr) {
	int intc_status = XIntc_GetIntrStatus(XPAR_INTC_0_BASEADDR);
	// Check the FIT interrupt first.
	if (intc_status & XPAR_FIT_TIMER_0_INTERRUPT_MASK){
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_FIT_TIMER_0_INTERRUPT_MASK);
		timer_interrupt_handler();
	}
	// Check the push buttons.
	if (intc_status & XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK){
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK);
		pb_interrupt_handler();
	}
}

int main (void) {
    init_platform();
    // Initialize the GPIO peripherals.
    int success;
    print("hello world\n\r");
    success = XGpio_Initialize(&gpPB, XPAR_PUSH_BUTTONS_5BITS_DEVICE_ID);
    // Set the push button peripheral to be inputs.
    XGpio_SetDataDirection(&gpPB, 1, 0x0000001F);
    // Enable the global GPIO interrupt for push buttons.
    XGpio_InterruptGlobalEnable(&gpPB);
    // Enable all interrupts in the push button peripheral.
    XGpio_InterruptEnable(&gpPB, 0xFFFFFFFF);

    microblaze_register_handler(interrupt_handler_dispatcher, NULL);
    XIntc_EnableIntr(XPAR_INTC_0_BASEADDR,
    		(XPAR_FIT_TIMER_0_INTERRUPT_MASK | XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK));
    XIntc_MasterEnable(XPAR_INTC_0_BASEADDR);
    microblaze_enable_interrupts();

    while(1);  // Program never ends.

    cleanup_platform();

    return 0;
}
