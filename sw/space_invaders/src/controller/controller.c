#include "controller.h"

static queue_t actionPtrQueue;

static bool moveLeft = false;
static bool moveRight = false;
static bool tankFire = false;

float parsefloat(uint32_t buffer);
bool actionQueuePop(controllerAction_t *action);

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
				/** Here are some thresholds **/

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

				// Set the direction of the movement
				if (action.y > THRESH_NO_MOVE) {
					moveLeft = true;
					moveRight = false;
				} else if (action.y < -THRESH_NO_MOVE) {
					moveLeft = false;
					moveRight = true;
				} else {
					moveLeft = false;
					moveRight = false;
				}

				// should I fire? (we could look at doing a unilateral test here)
				tankFire = (action.z < THRESH_FIRE || action.z > -THRESH_FIRE);

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
	if (queue_empty(&actionPtrQueue)) return false;

	// get the address of the top action struct ptr
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

	// we got something, so notify caller
	return true;
}
