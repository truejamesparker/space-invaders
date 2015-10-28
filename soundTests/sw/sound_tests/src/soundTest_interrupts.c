#include <stdio.h>
#include "platform.h"

#include "xparameters.h"

#include "soundDriver/xac97_l.h"

#include <xbasic_types.h>
#include <xio.h>
#include <xenv.h>
#include "mixer.h"
#include <stdint.h>
#include "sound.h"
#include "mb_interface.h"
#include "xintc_l.h"
#include "xgpio.h"

extern sound_t sound_tankShot;
extern sound_t sound_alienKilled;
extern sound_t sound_alienMove2;

XGpio gpPB;
static uint32_t sound_data[3000] = {0};

// Main interrupt dispatcher that calls the user-defined handlers
void interrupt_handler_dispatcher(void* ptr);

// ----------------------------------------------------------------------------

void interrupts_init() {
	microblaze_register_handler(interrupt_handler_dispatcher, NULL);
	XIntc_EnableIntr(XPAR_INTC_0_BASEADDR,
		(XPAR_FIT_TIMER_0_INTERRUPT_MASK | XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK));
	XIntc_MasterEnable(XPAR_INTC_0_BASEADDR);
	microblaze_enable_interrupts();
}

// ----------------------------------------------------------------------------

void interrupt_handler_dispatcher(void* ptr) {
	// Ask the Interrupt Controller for a status of its interrupts
	uint32_t status = XIntc_GetIntrStatus(XPAR_INTC_0_BASEADDR);

	// Check what triggered the interrupt
	if (status & XPAR_FIT_TIMER_0_INTERRUPT_MASK) {
		// Let the timer know it got an interrupt!
//		if (interrupts_timer_handler) interrupts_timer_handler();

		// Then acknowledge it so it can interrupt again
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_FIT_TIMER_0_INTERRUPT_MASK);
	} else if (status & XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK) {

		// ----------
		// Turn off all PB interrupts for now.
		XGpio_InterruptGlobalDisable(&gpPB);
		int i;
		static int j = 0;
		if(j==8){
			j=0;
		}
		play_track(j++);
		for(i=0; i<3000; i++){
			sound_data[i] = mix();
		}
		XAC97_PlayAudio(XPAR_AXI_AC97_0_BASEADDR, sound_data, &sound_data[3000]);
//		XAC97_PlayAudio(XPAR_AXI_AC97_0_BASEADDR, tankFireSound.data, &tankFireSound.data[tankFireSound.numSamples]);
//		XAC97_PlayAudio(XPAR_AXI_AC97_0_BASEADDR, soundalienKilled.data, &soundalienKilled.data[soundalienKilled.numSamples]);

		// Ack the PB interrupt.
		XGpio_InterruptClear(&gpPB, 0xFFFFFFFF);
		// Re-enable PB interrupts.
		XGpio_InterruptGlobalEnable(&gpPB);
		// ------

		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK);
	}
}

// ----------------------------------------------------------------------------



int main() {
    init_platform();

    // Initialize the GPIO peripherals.
	XGpio_Initialize(&gpPB, XPAR_PUSH_BUTTONS_5BITS_DEVICE_ID);
	// Set the push button peripheral to be inputs.
	XGpio_SetDataDirection(&gpPB, 1, 0x0000001F);
	// Enable the global GPIO interrupt for push buttons.
	XGpio_InterruptGlobalEnable(&gpPB);
	// Enable all interrupts in the push button peripheral.
	XGpio_InterruptEnable(&gpPB, 0xFFFFFFFF);

    interrupts_init();

    print("Hello World\n\r");

    // apparently we don't need to init it, just HardReset
    XAC97_HardReset(XPAR_AXI_AC97_0_BASEADDR);

    XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_ExtendedAudioStat, 1);
    XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCM_DAC_Rate, AC97_PCM_RATE_11025_HZ);

    int i=0;

    for(i=0; i < 3000; i++){
    	sound_data[i] = (sound_alienKilled.data[i] + sound_alienMove2.data[i])/2;
    }

    while (1);

    cleanup_platform();

    return 0;
}
