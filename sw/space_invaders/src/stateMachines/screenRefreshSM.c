#include "screenRefreshSM.h"

volatile uint8_t screenFrameIdx = SCREEN_MAIN_FRAME;

// ----------------------------------------------------------------------------

void screenRefreshSM_tick() {
	// All I do is refresh the screen, all day long.
	screen_refresh(screenFrameIdx);


	// --------------------------------
	// Screen Capture Support

	// Hardware, DMA-based screen capture
//	if (slideSwitches_isOn(SW_HW_CAPTURE)) screenCapture_hwSave();

	// Software, slow screen capture
	if (slideSwitches_isOn(SW_SW_CAPTURE)) screenCapture_swSave();

	// Display the saved screen capture
	if (slideSwitches_isOn(SW_SHOW_CAPTURE)) {
		// pause the game so we can see our capture!
//		gamePlaySM_pauseGame();

		screenCapture_show();
	} else {
//		gamePlaySM_resumeGame();
	}
	// --------------------------------
}
