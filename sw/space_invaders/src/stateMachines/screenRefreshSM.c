#include "screenRefreshSM.h"

volatile uint8_t screenFrameIdx = SCREEN_MAIN_FRAME;

volatile bool swCapturedPreviously = false;

// ----------------------------------------------------------------------------

void screenRefreshSM_tick() {
	// All I do is refresh the screen, all day long.
	screen_refresh(screenFrameIdx);


	// --------------------------------
	// Screen Capture Support

	// If game is paused, don't even do this stuff
//	// If slideSwitch 0 is on, then pause the game.
//	if (slideSwitches_isOn(SW_PAUSE)) gamePlaySM_pauseGame();
//	else gamePlaySM_resumeGame();

	// Hardware, DMA-based screen capture
//	if (slideSwitches_isOn(SW_HW_CAPTURE)) screen_hwCapture();

	// Software, slow screen capture
	if (slideSwitches_isOn(SW_SW_CAPTURE)) {
		if (!swCapturedPreviously) {
			gamePlaySM_pauseGame();
			screen_swCapture();
			gamePlaySM_resumeGame();
			swCapturedPreviously = true;
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
		//        off a captured frame)
		if (screenFrameIdx != SCREEN_MAIN_FRAME) {
			gamePlaySM_resumeGame();
			screenFrameIdx = SCREEN_MAIN_FRAME;
		}
	}

	// --------------------------------
}
