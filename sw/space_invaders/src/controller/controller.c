#include "controller.h"

volatile static queue_t actionsShadow;
volatile static controllerAction_t actions[CONTROLLER_ACTION_COUNT];

volatile static bool moveLeft = false;
volatile static bool moveRight = false;
volatile static bool tankFire = false;

float parsefloat(uint32_t buffer);
bool actionQueuePop(controllerAction_t *action);

// ----------------------------------------------------------------------------

void controller_init() {
	// setup the action shadow queue
	// This queue's purpose is to try and be as DRY as possible.
	// Since I couldn't think of a clean why of reusing the queue
	// code (since BLE uses uint32_t but controller needs a struct)
	// I'm using the queue to simply keep track of what my current
	// index is, and if I'm empty or full.
	queue_init(&actionsShadow, CONTROLLER_ACTION_COUNT);
}

// ----------------------------------------------------------------------------

void controller_queueAction(controllerAction_t action) {
	// store to our local queue
	actions[actionsShadow.indexIn] = action;

	// push the address to our shadow queue to keep track of indices
	// We will be using the queue shadow to point into our local array
	// this eliminates the need to malloc() in an ISR
	queue_overwritePush(&actionsShadow, (uint32_t)&actions[actionsShadow.indexIn]);
}

// ----------------------------------------------------------------------------

void controller_process() {

	// get an action to process
	controllerAction_t action;
	if (actionQueuePop(&action)) {
		// Only try to process the action if there was
		// an action that came off the queue

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

				// Set the speed of the movement
				if (action.y < -THRESH_VERY_FAST || action.y > THRESH_VERY_FAST) {
					controllerSM_updateTankSpeed(CONTROLLER_TANK_MOVE_VERY_FAST);
				} else if (action.y < -THRESH_FAST || action.y > THRESH_FAST) {
					controllerSM_updateTankSpeed(CONTROLLER_TANK_MOVE_FAST);
				} else if (action.y < -THRESH_REGULAR || action.y > THRESH_REGULAR) {
					controllerSM_updateTankSpeed(CONTROLLER_TANK_MOVE_REGULAR);
				} else if (action.y < -THRESH_SLOW || action.y > THRESH_SLOW) {
					controllerSM_updateTankSpeed(CONTROLLER_TANK_MOVE_SLOW);
				}
//				9;
//				uint32_t tmp = (uint32_t)action.y;
//				xil_printf("%x", tmp);



				// Set the direction of the movement
				if (action.y > THRESH_NO_MOVE) {
					moveLeft = true;
					moveRight = false;
//					xil_printf("left\r\n");
				} else if (action.y < -THRESH_NO_MOVE) {
					moveLeft = false;
					moveRight = true;
//					xil_printf("right\r\n");
				} else {
					moveLeft = false;
					moveRight = false;
//					xil_printf("none\r\n");
				}

				// should I fire? (we could look at doing a unilateral test here)
				tankFire = (action.z < -THRESH_FIRE || action.z > THRESH_FIRE);

				break;
			default:
				break;
		}
	}

	// Do some tank actions
	if 		(moveLeft) tank_left();
	else if (moveRight) tank_right();

	if (tankFire) missiles_tankFire();
}

// ----------------------------------------------------------------------------
// Private Helper Methods
// ----------------------------------------------------------------------------

bool actionQueuePop(controllerAction_t *action) {
	// make sure there is something to get!
	if (queue_empty(&actionsShadow)) return false;

	// get the address of the top action struct ptr (local array)
	uint32_t actionPtrAddr = queue_pop(&actionsShadow);
	controllerAction_t *actionPtr = (controllerAction_t *)actionPtrAddr;

	// deep copy over the data!
	action->type = actionPtr->type;
	action->btnNumber = actionPtr->btnNumber;
	action->pressed = actionPtr->pressed;
	action->x = actionPtr->x;
	action->y = actionPtr->y;
	action->z = actionPtr->z;

	// we got something, so notify caller
	return true;
}
