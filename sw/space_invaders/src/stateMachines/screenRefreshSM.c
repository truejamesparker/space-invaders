#include "screenRefreshSM.h"

volatile static uint8_t screenFrameIdx = SCREEN_MAIN_FRAME;

volatile static bool swCapturedPreviously = false;
volatile static bool hwCapturedPreviously = false;

// ----------------------------------------------------------------------------

void screenRefreshSM_tick() {
	// All I do is refresh the screen, all day long.
	screen_refresh(screenFrameIdx);


	// --------------------------------
	// Screen Capture Support

	// If game is paused, don't even do this stuff
	// If slideSwitch 0 is on, then pause the game.
	if (slideSwitches_isOn(SW_PAUSE)) gamePlaySM_pauseGame();
	else {
		// Only resume if !SW_PAUSE and I'm in normal game play
		// (i.e., not screen capturing or showing a capture)
		if (screenFrameIdx == SCREEN_MAIN_FRAME) gamePlaySM_resumeGame();
	}

	// Hardware, DMA-based screen capture
	if (slideSwitches_isOn(SW_HW_CAPTURE)) {
		if (!hwCapturedPreviously) {

			// start the timer
			timer_start();

			screen_hwCapture();

			// so we don't keep capturing while switch is high
			hwCapturedPreviously = true;

			// the timer will be stopped in the DMA interrupt
			// (below) and will print out the timing there...
		}
	} else {
		hwCapturedPreviously = false;
	}

	// Software, slow screen capture
	if (slideSwitches_isOn(SW_SW_CAPTURE)) {
		if (!swCapturedPreviously) {

			// start the timer
			timer_start();

			gamePlaySM_pauseGame();
			screen_swCapture();
			gamePlaySM_resumeGame();

			// so we don't keep capturing while switch is high
			swCapturedPreviously = true;

			// stop the timer and print out time
			uint32_t elapsedTime = 0;
			timer_stop(&elapsedTime);
			xil_printf("Software Capture, elapsed time: %d\r\n", elapsedTime);
		}
	} else {
		swCapturedPreviously = false;
	}

	// Display the saved screen capture
	if (slideSwitches_isOn(SW_SHOW_CAPTURE)) {
		// pause the game so we can see our capture!
		gamePlaySM_pauseGame();
		screenFrameIdx = SCREEN_CAPTURE_FRAME;
	} else {
		// Only resume the game if the SCREEN_MAIN_FRAME
		// is not already the frame being refreshed.
		// (i.e., if I was paused because I was showing
		//        a captured frame)
		if (screenFrameIdx != SCREEN_MAIN_FRAME) {
			gamePlaySM_resumeGame();
			screenFrameIdx = SCREEN_MAIN_FRAME;
		}
	}

	// --------------------------------
}

// ----------------------------------------------------------------------------

void screenRefreshSM_hwCaptureDone() {
	// stop the timer that was started above when the switch was on

	uint32_t elapsedTime = 0;
	timer_stop(&elapsedTime);

	xil_printf("Hardware Capture, elapsed time: %d\r\n", elapsedTime);
}
