#include "screen.h"

static XAxiVdma videoDMAController;

static unsigned int* framePointer;
static unsigned int* bgFramePointer;
static unsigned int* captureFramePointer;

//-----------------------------------------------------------------------------

void screen_init() {
	// There are 3 steps to initializing the vdma driver and IP.
	// Step 1: lookup the memory structure that is used to access the vdma driver.
	XAxiVdma_Config* VideoDMAConfig = XAxiVdma_LookupConfig(
			XPAR_AXI_VDMA_0_DEVICE_ID);

	// Step 2: Initialize the memory structure and the hardware.
	if (XST_FAILURE == XAxiVdma_CfgInitialize(&videoDMAController,
			VideoDMAConfig, XPAR_AXI_VDMA_0_BASEADDR)) {
		xil_printf("VideoDMA Did not initialize.\r\n");
	}

	// Step 3: (optional) set the frame store number.
	if (XST_FAILURE == XAxiVdma_SetFrmStore(&videoDMAController, SCREEN_FRAME_COUNT,
			XAXIVDMA_READ)) {
		xil_printf("Set Frame Store Failed.");
	}
	// Initialization is complete at this point.

	// Setup the frame counter. We want two read frames. We don't need any write frames but the
	// function generates an error if you set the write frame count to 0. We set it to 2
	// but ignore it because we don't need a write channel at all.
	XAxiVdma_FrameCounter myFrameConfig;
	myFrameConfig.ReadFrameCount = SCREEN_FRAME_COUNT;
	myFrameConfig.ReadDelayTimerCount = 10;
	myFrameConfig.WriteFrameCount = SCREEN_FRAME_COUNT;
	myFrameConfig.WriteDelayTimerCount = 10;
	int status = XAxiVdma_SetFrameCounter(&videoDMAController, &myFrameConfig);
	if (status != XST_SUCCESS) {
		xil_printf("Set frame counter failed %d\r\n", status);
		if (status == XST_VDMA_MISMATCH_ERROR)
			xil_printf("DMA Mismatch Error\r\n");
	}

	// Now we tell the driver about the geometry of our frame buffer and a few other things.
	// Our image is 480 x 640.
	XAxiVdma_DmaSetup myFrameBuffer;
	myFrameBuffer.VertSizeInput = SCREEN_HEIGHT; // 480 vertical pixels.
	myFrameBuffer.HoriSizeInput = SCREEN_WIDTH * 4; // 640 horizontal (32-bit pixels).
	myFrameBuffer.Stride = SCREEN_WIDTH * 4; // Dont' worry about the rest of the values.
	myFrameBuffer.FrameDelay = 0;
	myFrameBuffer.EnableCircularBuf = 1;
	myFrameBuffer.EnableSync = 0;
	myFrameBuffer.PointNum = 0;
	myFrameBuffer.EnableFrameCounter = 0;
	myFrameBuffer.FixedFrameStoreAddr = 0;
	if (XST_FAILURE == XAxiVdma_DmaConfig(&videoDMAController, XAXIVDMA_READ,
			&myFrameBuffer)) {
		xil_printf("DMA Config Failed\r\n");
	}
	// We need to give the frame buffer pointers to the memory that it will use. This memory
	// is where you will write your video data. The vdma IP/driver then streams it to the HDMI
	// IP.
	myFrameBuffer.FrameStoreStartAddr[0] = FRAME_BUFFER_0_ADDR;
	myFrameBuffer.FrameStoreStartAddr[1] = FRAME_BUFFER_0_ADDR + 4 * 640 * 480;
	myFrameBuffer.FrameStoreStartAddr[2] = FRAME_BUFFER_0_ADDR + 4 * 640 * 480;

	if (XST_FAILURE == XAxiVdma_DmaSetBufferAddr(&videoDMAController,
			XAXIVDMA_READ, myFrameBuffer.FrameStoreStartAddr)) {
		xil_printf("DMA Set Address Failed Failed\r\n");
	}
	// Print a sanity message if you get this far.
	//	xil_printf("Woohoo! I made it through initialization.\n\r");

	// Now, let's get ready to start displaying some stuff on the screen.
	// The variables framePointer and framePointer1 are just pointers to the base address
	// of frame 0 and frame 1.
	framePointer = (unsigned int *) FRAME_BUFFER_0_ADDR;
	bgFramePointer = (unsigned int*) (FRAME_BUFFER_0_ADDR + 4 * 640 * 480);
	captureFramePointer = (unsigned int*) (FRAME_BUFFER_0_ADDR + 4 * 640 * 480);

	// This tells the HDMI controller the resolution of your display (there must be a better way to do this).
	XIo_Out32(XPAR_AXI_HDMI_0_BASEADDR, SCREEN_WIDTH*SCREEN_HEIGHT);

	// Start the DMA for the read channel only.
	if (XST_FAILURE == XAxiVdma_DmaStart(&videoDMAController, XAXIVDMA_READ)) {
		xil_printf("DMA START FAILED\r\n");
	}

	// We have two frames, let's park on frame 0. Use frameIndex to index them.
	// Note that you have to start the DMA process before parking on a frame.

	screen_clear();
	if (XST_FAILURE == XAxiVdma_StartParking(&videoDMAController, SCREEN_MAIN_FRAME,
			XAXIVDMA_READ)) {
		xil_printf("vdma parking failed\n\r");
	}
}

//-----------------------------------------------------------------------------

// clear out the screen (fill black)
void screen_clear() {
	uint32_t x = 0;
	uint32_t y = 0;

	// loop through each pixel
	for (y = 0; y < SCREEN_HEIGHT; y++) {
		for (x = 0; x < SCREEN_WIDTH; x++) {

			SCREEN_SET_XY_TO_COLOR(x, y, SCREEN_COLOR_BLACK);
			SCREEN_BG_SET_XY_TO_COLOR(x, y, SCREEN_COLOR_BLACK);

#if SCREEN_SHOW_MARGINS
			if (	x == SCREEN_EDGE_BUFFER ||
					y == SCREEN_EDGE_BUFFER ||
					x == SCREEN_WIDTH-SCREEN_EDGE_BUFFER-1 ||
					y == SCREEN_HEIGHT-SCREEN_EDGE_BUFFER-1) {
				SCREEN_SET_XY_TO_COLOR(x,y,SCREEN_ELEM_OUTLINE);
				SCREEN_BG_SET_XY_TO_COLOR(x, y, SCREEN_ELEM_OUTLINE);
			}
#endif
		}
	}
}

//-----------------------------------------------------------------------------

// repark the screen pointer
void screen_refresh() {
	if (XST_FAILURE == XAxiVdma_StartParking(&videoDMAController, SCREEN_MAIN_FRAME,
			XAXIVDMA_READ)) {
		xil_printf("vdma parking failed\n\r");
	}
}

//-----------------------------------------------------------------------------

// draw the given symbol at the given locations with the appropriate scale applied
void screen_drawSymbol(const uint32_t* symbol, point_t origin, symbolsize_t size, uint16_t scale, uint32_t onColor) {
	// drawing a symbol is the same as shifting it by (0,0)
	screen_shiftElement(symbol, origin, size, 0, 0, scale, onColor);
}

//-----------------------------------------------------------------------------

void screen_bgDrawSymbol(const uint32_t* symbol, point_t origin, symbolsize_t size, uint16_t scale, uint32_t onColor) {
	uint32_t row = 0, col = 0, i = 0, j = 0, x_offset = 0, y_offset = 0;
	for (row = 0; row < size.h; row++) {
		x_offset = 0;
		for (col = 0; col < size.w; col++) {
			if(symbol[row] & (1 << (size.w - 1 - col))){
				// now scale that pixel on the screen
				for (i = 0; i < scale; i++) {
					for (j = 0; j < scale; j++) {
						SCREEN_BG_SET_XY_TO_COLOR(origin.x+i+x_offset,origin.y+j+y_offset, onColor);
					}
				}
			}
			x_offset += scale; // account for the scale in x
		}
		y_offset += scale; // account for the scale in y
	}
}

//-----------------------------------------------------------------------------

// return bg color at screen coordinates (x,y)
uint32_t screen_getBgColor(uint16_t x, uint16_t y){
	return bgFramePointer[SCREEN_XY_TO_INDEX((x),(y))];
}

//-----------------------------------------------------------------------------
// return screen color at screen coordinates (x,y)
uint32_t screen_getScreenColor(uint16_t x, uint16_t y){
	return framePointer[SCREEN_XY_TO_INDEX((x),(y))];
}

//-----------------------------------------------------------------------------

void screen_shiftElement(const uint32_t* symbol, point_t origin, symbolsize_t size, int16_t dx, int16_t dy, uint16_t scale, uint32_t onColor){
	uint32_t row = 0, col = 0, i = 0, j = 0, x_offset = 0, y_offset = 0, color;
	int8_t xSign, ySign;
	int8_t xShiftOffset = 0, yShiftOffset = 0;

	if (dx < 0) {
		// shift left, clear right
		xSign = SCREEN_SHIFT_LEFT;
		dx = -1*dx; // abs(dx)
		xShiftOffset = dx*scale;
	} else {
		// shift right, clear left
		xSign = SCREEN_SHIFT_RIGHT;
	}

	if (dy < 0) {
		ySign = SCREEN_SHIFT_UP;
		dy = -1*dy; // abs(dy)
		yShiftOffset = dy*scale;
	} else {
		ySign = SCREEN_SHIFT_DOWN;
	}

	// loop through every pixel in the bitmap
	for (row = 0; row < size.h+dy; row++) {
		x_offset = 0;
		for (col = 0; col < size.w+dx; col++) {

			// now scale that pixel
			for (i = 0; i < scale; i++) {
				for (j = 0; j < scale; j++) {

					// Get the current (x,y) for the given loop iteration, etc.
					uint16_t x = origin.x + i + x_offset - xShiftOffset;
					uint16_t y = origin.y + j + y_offset - yShiftOffset;

					// Get the background color from the secondary background frame.
					// This is important for drawing over bunkers, aliens, etc.
					uint32_t bgcolor = screen_getBgColor(x, y);

					// Figure out what color to make things
					if (xSign == SCREEN_SHIFT_RIGHT && col < dx) {
						color = bgcolor;

					} else if (xSign == SCREEN_SHIFT_LEFT && col >= size.w) {
						color = bgcolor;

					} else if (ySign == SCREEN_SHIFT_DOWN && row < dy) {
						color = bgcolor;

					} else if (ySign == SCREEN_SHIFT_UP && (row >= size.h)) {
						color = bgcolor;

					} else if (xSign == SCREEN_SHIFT_LEFT || ySign == SCREEN_SHIFT_UP) {
						color = (symbol[row] & (1 << (size.w - 1 - (col)))) ? onColor : bgcolor;

					} else if (xSign == SCREEN_SHIFT_RIGHT || ySign == SCREEN_SHIFT_DOWN) {
						color = (symbol[row-dy] & (1 << (size.w - 1 - (col-dx)))) ? onColor : bgcolor;

					} else {
						// this branch should never be evaluated. If you see yellow, you see errors
						color = SCREEN_COLOR_YELLOW;
					}

					// if the color is SCREEN_BG_COLOR we assume we
					// want to use the pixel color of the background
					if (onColor == SCREEN_BG_COLOR) color = bgcolor;


#if SCREEN_SHIFT_BOX
					if (xSign == SCREEN_SHIFT_LEFT || xSign == SCREEN_SHIFT_RIGHT) {
						if (col == dx || col == size.w+dx-1 || row == 0 || row == size.h-1) {
							color = SCREEN_ELEM_OUTLINE;
						}

						if (col == 0 || col == size.w-1) {
							color = SCREEN_ELEM_DIFF_OUTLINE;
						}
					}
#endif

#if SCREEN_SHOW_ORIGIN
					if (xSign == SCREEN_SHIFT_RIGHT) {
						if (col == dx && row == dy) color = SCREEN_ORIGIN_COLOR;
					} else if (xSign == SCREEN_SHIFT_LEFT) {
						if (col == 0 && row == dy) color = SCREEN_ORIGIN_COLOR;
					}
#endif

					// Only set the screen color if within the bounds of the screen.
					// This turns off image wrapping. This works because (x,y) are unsigned.
					// Therefore, when it goes below the screen's origin (0,0) the numbers
					// actually get bigger than the screen width and height.
					if (x < SCREEN_WIDTH && y < SCREEN_HEIGHT) SCREEN_SET_XY_TO_COLOR(x, y, color);
				}
			}
			x_offset += scale; // account for scale in x
		}
		y_offset += scale; // account for scale in y
	}
}

//-----------------------------------------------------------------------------
// Private Helper Methods
//-----------------------------------------------------------------------------
