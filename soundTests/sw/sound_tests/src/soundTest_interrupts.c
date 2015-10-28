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

#define BTN_LEFT_MASK		0x08
#define BTN_RIGHT_MASK		0x02
#define BTN_DOWN_MASK		0x04
#define BTN_UP_MASK			0x10
#define BTN_CENTER_MASK		0x01
#define BTN_ANY_MASK		0xFF
#define BUFFER_SIZE 		512
#define MAX_FIFO_SAMPLES	BUFFER_SIZE/2
#define VOL_LEVELS			32

static uint32_t volumes[VOL_LEVELS] = {
	AC97_VOL_ATTN_0_DB,
	AC97_VOL_ATTN_1_5_DB,
	AC97_VOL_ATTN_3_0_DB,
	AC97_VOL_ATTN_4_5_DB,
	AC97_VOL_ATTN_6_0_DB,
	AC97_VOL_ATTN_7_5_DB,
	AC97_VOL_ATTN_9_0_DB,
	AC97_VOL_ATTN_10_0_DB,
	AC97_VOL_ATTN_11_5_DB,
	AC97_VOL_ATTN_13_0_DB,
	AC97_VOL_ATTN_14_5_DB,
	AC97_VOL_ATTN_16_0_DB,
	AC97_VOL_ATTN_17_5_DB,
	AC97_VOL_ATTN_19_0_DB,
	AC97_VOL_ATTN_20_5_DB,
	AC97_VOL_ATTN_22_0_DB,
	AC97_VOL_ATTN_23_5_DB,
	AC97_VOL_ATTN_25_0_DB,
	AC97_VOL_ATTN_26_5_DB,
	AC97_VOL_ATTN_28_0_DB,
	AC97_VOL_ATTN_29_5_DB,
	AC97_VOL_ATTN_31_0_DB,
	AC97_VOL_ATTN_32_5_DB,
	AC97_VOL_ATTN_34_0_DB,
	AC97_VOL_ATTN_35_5_DB,
	AC97_VOL_ATTN_37_0_DB,
	AC97_VOL_ATTN_38_5_DB,
	AC97_VOL_ATTN_40_0_DB,
	AC97_VOL_ATTN_41_5_DB,
	AC97_VOL_ATTN_43_0_DB,
	AC97_VOL_ATTN_44_5_DB,
	AC97_VOL_ATTN_46_0_DB,
};

extern int tankFireSoundRate;
extern int tankFireSoundFrames;
extern int tankFireSound[];

extern sound_t sound_alienMove1;
extern sound_t sound_alienMove2;
extern sound_t sound_alienMove3;
extern sound_t sound_alienMove4;
extern sound_t sound_tankShot;

XGpio gpPB;
static uint8_t vol_level = 0;
static sound_t *soundPtr;
static uint32_t currentSampleNum;

// Main interrupt dispatcher that calls the user-defined handlers
void interrupt_handler_dispatcher(void* ptr);
void fifo_interrupt_handler();
uint32_t getCurrentSample();
void pb_interrupt_handler(uint32_t state);
void volume_up();
void volume_down();

void volume_down(){
	vol_level = (vol_level==VOL_LEVELS-1) ? vol_level : ++vol_level; // don't dec if maxed out
	uint32_t vol  = AC97_VOL_MAX + volumes[vol_level];
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCMOutVol, vol);
}

void volume_up(){
	vol_level = (vol_level==0) ? vol_level : --vol_level; // don't dec if maxed out
	uint32_t vol = AC97_VOL_MAX + volumes[vol_level];
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCMOutVol, vol);
}

// ----------------------------------------------------------------------------

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

		u32 currentButtonState = XGpio_DiscreteRead(&gpPB, 1);

		pb_interrupt_handler(currentButtonState);

//		XAC97_PlayAudio(XPAR_AXI_AC97_0_BASEADDR, sound_alienMove2.data, &sound_alienMove2.data[sound_alienMove2.numSamples]);

		// Ack the PB interrupt.
		XGpio_InterruptClear(&gpPB, 0xFFFFFFFF);
		// Re-enable PB interrupts.
		XGpio_InterruptGlobalEnable(&gpPB);
		// ------

		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK);
	} else if (status & XPAR_AXI_AC97_0_INTERRUPT_MASK) {

		fifo_interrupt_handler();

		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_AXI_AC97_0_INTERRUPT_MASK);
	}
}

// ----------------------------------------------------------------------------

void pb_interrupt_handler(uint32_t state) {
	if (state & BTN_LEFT_MASK) {
		play_track(SOUND_TANK_SHOT);
	} else if (state & BTN_CENTER_MASK) {
		play_track(SOUND_ALIEN_MOVE2);
	} else if (state & BTN_RIGHT_MASK) {
		play_track(SOUND_ALIEN_MOVE3);
	} else if (state & BTN_DOWN_MASK) {
		volume_down();
	} else if (state & BTN_UP_MASK) {
		volume_up();
	}
}

// ----------------------------------------------------------------------------

uint32_t getCurrentSample() {

	if (soundPtr == NULL) return 0;

	uint32_t sampleLength = soundPtr->numSamples;

	// if I'm done, then play a 0
	if (currentSampleNum == sampleLength) return 0;

	uint32_t currentSample = soundPtr->data[currentSampleNum];

	currentSampleNum++;

	return currentSample;
}

// ----------------------------------------------------------------------------


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

    print("made it past interrupts_init\n\r");

    // apparently we don't need to init it, just HardReset
    XAC97_HardReset(XPAR_AXI_AC97_0_BASEADDR);
    XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_ExtendedAudioStat, 1);
    XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCM_DAC_Rate, AC97_PCM_RATE_11025_HZ);
    XAC97_mSetControl(XPAR_AXI_AC97_0_BASEADDR, AC97_ENABLE_IN_FIFO_INTERRUPT);
    XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_MasterVol, AC97_VOL_MAX);
    XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCMOutVol, AC97_VOL_MAX);


    while (1);

    cleanup_platform();

    return 0;
}
