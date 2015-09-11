#include <stdio.h>          // xil_printf and so forth.
#include <stdint.h>			// uint32_t and so forth.

#include "xgpio.h"          // Provides access to PB GPIO driver.
#include "platform.h"       // Enables caching and other system stuff.
#include "mb_interface.h"   // provides the microblaze interrupt enables, etc.
#include "xintc_l.h"        // Provides handy macros for the interrupt controller.


#define MAX_SECONDS 60
#define MAX_MINUTES 60
#define MAX_HOURS 	23
#define TICK_FOR

XGpio gpLED;  // This is a handle for the LED GPIO block.
XGpio gpPB;   // This is a handle for the push-button GPIO block.

static volatile uint32_t _currentButtonState = 0;
static volatile uint8_t _debounceEnabled = 0;
static volatile uint8_t _debounceCounter = 0;

static volatile uint8_t counter = 0; // tens of milliseconds
static volatile uint32_t _seconds = 0;
static volatile uint32_t _minutes = 0;
static volatile uint32_t _hours = 0;

// This is invoked in response to a timer interrupt.
// It does 2 things: 1) debounce switches, and 2) advances the time.
void timer_interrupt_handler() {

	// ------------
	// Clock
	// ------------
	if (++counter == 100){

		// clear the counter, it's been a second
		counter = 0;

		// increment the clock
		if (++_seconds == MAX_SECONDS) _seconds = 0;
		if (!_seconds && ++_minutes == MAX_MINUTES) _minutes = 0;
		if (!_seconds && !_minutes && ++_hours == MAX_HOURS) _hours = 0;

		// Print to the screen
		xil_printf("\b\b\b\b\b\b\b\b%02d:%02d:%02d", _hours, _minutes, _seconds);

	}

	// ------------------
	// Button Debouncing
	// ------------------
	if (_debounceEnabled && ++_debounceCounter == 5) {
		xil_printf("Buttons: 0x%x\r\n", _currentButtonState);
		_debounceEnabled = 0;
	}

}

// This is invoked each time there is a change in the button state (result of a push or a bounce).
void pb_interrupt_handler() {
	// Clear the GPIO interrupt.
	XGpio_InterruptGlobalDisable(&gpPB);                // Turn off all PB interrupts for now.
	uint32_t currentButtonState = XGpio_DiscreteRead(&gpPB, 1);  // Get the current state of the buttons.

	// ---------------------------------------------

	// Turn debouncing on if there is a change in button state
	if (currentButtonState != _currentButtonState) {
		_currentButtonState = currentButtonState;
		_debounceEnabled = 1;
		_debounceCounter = 0;
	}

	// ---------------------------------------------

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
