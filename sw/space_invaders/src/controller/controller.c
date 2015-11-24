#include "controller.h"

static queue_t actionPtrQueue;

static bool moveLeft = false;
static bool moveRight = false;
static bool tankFire = false;

float parsefloat(uint32_t buffer);
void actionQueuePop(controllerAction_t *action);

// ----------------------------------------------------------------------------

void controller_init() {
	// setup the action queue
	queue_init(&actionPtrQueue, CONTROLLER_QUEUE_LENGTH);
}

// ----------------------------------------------------------------------------

void controller_queueAction(controllerAction_t action) {
	// create some memory for this action
	controllerAction_t *actionPtr;
	actionPtr = malloc(sizeof(controllerAction_t));

	// copy the contents of the incoming action to this memory allocated action
	actionPtr->type = action.type;
	actionPtr->btnNumber = action.btnNumber;
	actionPtr->pressed = action.pressed;
	actionPtr->x = action.x;
	actionPtr->y = action.y;
	actionPtr->z = action.z;

	// push the address to the actionPtrQueue
	queue_overwritePush(&actionPtrQueue, (uint32_t)actionPtr);
}

// ----------------------------------------------------------------------------

bool controller_process() {

	// get an action to process
	controllerAction_t action;
	actionQueuePop(&action);

	switch(action.type) {
		case BLE_BUTTON:

			// since button events are only fired on
			// PRESSED and RELEASED, this creates a 'latching'
			// effect, i.e., you may hold down the buttons
			// without having to press/release repeatedly
			if (action.btnNumber == CONTROLLER_BTN_LEFT) {
				moveLeft = action.pressed;
				if (moveLeft) moveRight = false;
			} else if (action.btnNumber == CONTROLLER_BTN_RIGHT) {
				moveRight = action.pressed;
				if (moveRight) moveLeft = false;
			}

			if (action.btnNumber == CONTROLLER_BTN_FIRE) {
				tankFire = action.pressed;
			}

			break;
		case BLE_ACCEL:
			/** Here are some thresholds **/

			if (action.y < -0.8) {
//				xil_printf("move right 4x\r\n");
			} else if (action.y < -0.55) {
//				xil_printf("move right 3x\r\n");
			} else if (action.y < -0.3) {
//				xil_printf("move right 2x\r\n");
			} else if (action.y < -0.1) {
//				xil_printf("move right 1x\r\n");
			}

//			if (y > 0.8) {
//				xil_printf("move left 4x\r\n");
//			} else if (y > 0.55) {
//				xil_printf("move left 3x\r\n");
//			} else if (y > 0.3) {
//				xil_printf("move left 2x\r\n");
//			} else if (y > 0.1) {
//				xil_printf("move left 1x\r\n");
//			}

			break;
		default:
			break;
	}

	// Do some tank actions
	if 		(moveLeft) tank_left();
	else if (moveRight) tank_right();

	if (tankFire) missiles_tankFire();

	return false;
}

// ----------------------------------------------------------------------------

bool controller_leftPressed() {

	return false;

//	if (readPacket(CONTROLLER_PACKET_PARSER_TIMEOUT)) {
////    		xil_printf("Got something: %s\r\n", packetbuffer);
//
//
//		// Buttons
//		if (packetbuffer[1] == 'B') {
//			uint8_t btnNum = packetbuffer[2] - '0';
//			uint8_t pressed = packetbuffer[3] - '0';
//			xil_printf("Button %d", btnNum);
//			if (pressed) xil_printf(" pressed\r\n");
//			else 		 xil_printf(" released\r\n");
//
//			if      (btnNum == 7 &&  pressed) _moveLeft = true;
//			else if (btnNum == 7 && !pressed) _moveLeft = false;
//		}
//
//		// Accelerometer
////		if (packetbuffer[1] == 'A') {
////			float x, y, z;
//////				x = parsefloat(packetbuffer+2);
//////				y = parsefloat(packetbuffer+6);
//////				z = parsefloat(packetbuffer+10);
////
//////				printf("Y: %.4f\r\n", 1.1f);
////
//////				xil_printf("A: %c%c 0x",packetbuffer[0], packetbuffer[1]);
////
////
////			// There seems to be an endian mismatch...
////			uint32_t tempX = ((uint8_t)packetbuffer[2]) << 0;
////			tempX = tempX | ((uint8_t)packetbuffer[3]) << 8;
////			tempX = tempX | ((uint8_t)packetbuffer[4]) << 16;
////			tempX = tempX | ((uint8_t)packetbuffer[5]) << 24;
////
////			uint32_t tempY = ((uint8_t)packetbuffer[6]) << 0;
////			tempY = tempY | ((uint8_t)packetbuffer[7]) << 8;
////			tempY = tempY | ((uint8_t)packetbuffer[8]) << 16;
////			tempY = tempY | ((uint8_t)packetbuffer[9]) << 24;
////
////			uint32_t tempZ = ((uint8_t)packetbuffer[10]) << 0;
////			tempZ = tempZ | ((uint8_t)packetbuffer[11]) << 8;
////			tempZ = tempZ | ((uint8_t)packetbuffer[12]) << 16;
////			tempZ = tempZ | ((uint8_t)packetbuffer[13]) << 24;
////
////
////			// having printed out the data in this format,
////			// you can load it into MATLAB to process it
////			// and view what the accelerometer data looks like
////			xil_printf("%x %x %x\r\n", tempX, tempY, tempZ);
////
////
////			x = parsefloat(tempX);
////			y = parsefloat(tempY);
////			z = parsefloat(tempZ);
////
////
////			/** Here are some thresholds **/
////
//////				if (y < -0.8) {
//////					xil_printf("move right 4x\r\n");
//////				} else if (y < -0.55) {
//////					xil_printf("move right 3x\r\n");
//////				} else if (y < -0.3) {
//////					xil_printf("move right 2x\r\n");
//////				} else if (y < -0.1) {
//////					xil_printf("move right 1x\r\n");
//////				}
//////
//////				if (y > 0.8) {
//////					xil_printf("move left 4x\r\n");
//////				} else if (y > 0.55) {
//////					xil_printf("move left 3x\r\n");
//////				} else if (y > 0.3) {
//////					xil_printf("move left 2x\r\n");
//////				} else if (y > 0.1) {
//////					xil_printf("move left 1x\r\n");
//////				}
////
//////				xil_printf("Accel\tx: "); printFloat(x);
//////				xil_printf("\t\ty:"); printFloat(y);
//////				xil_printf("\t\tz:"); printFloat(z);
//////				xil_printf("\r\n");
////		}
//
//	}


//	return _moveLeft;


}

// ----------------------------------------------------------------------------

bool controller_rightPressed() {

//	if (readPacket(CONTROLLER_PACKET_PARSER_TIMEOUT)) {
//	//    		xil_printf("Got something: %s\r\n", packetbuffer);
//
//
//			// Buttons
//			if (packetbuffer[1] == 'B') {
//				uint8_t btnNum = packetbuffer[2] - '0';
//				uint8_t pressed = packetbuffer[3] - '0';
//				xil_printf("Button %d", btnNum);
//				if (pressed) xil_printf(" pressed\r\n");
//				else 		 xil_printf(" released\r\n");
//
//				if      (btnNum == 8 &&  pressed) _moveRight = true;
//				else if (btnNum == 8 && !pressed) _moveRight = false;
//			}
//	}

//	return _moveRight;

	return false;
}

// ----------------------------------------------------------------------------
// Private Helper Methods
// ----------------------------------------------------------------------------

void actionQueuePop(controllerAction_t *action) {
	uint32_t actionPtrAddr = queue_pop(&actionPtrQueue);
	controllerAction_t *actionPtr = (controllerAction_t *)actionPtrAddr;

	// deep copy over so we can free memory
	action->type = actionPtr->type;
	action->btnNumber = actionPtr->btnNumber;
	action->pressed = actionPtr->pressed;
	action->x = actionPtr->x;
	action->y = actionPtr->y;
	action->z = actionPtr->z;

	// make sure to free the memory we allocated!
	free(actionPtr);
}
