#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../ble/ble.h"
#include "../queue/queue.h"
#include "../elements/tank.h"
#include "../elements/missiles.h"
#include "../stateMachines/controllerSM.h"

#define CONTROLLER_ACTION_COUNT			32

#define CONTROLLER_BTN_LEFT				7
#define CONTROLLER_BTN_RIGHT			8
#define CONTROLLER_BTN_FIRE				1

#define THRESH_VERY_FAST	(0.7f)
#define THRESH_FAST			(0.55f)
#define THRESH_REGULAR		(0.4f)
#define THRESH_SLOW			(0.26f)
#define THRESH_NO_MOVE		(0.25f)
#define THRESH_FIRE			(1.5f)

typedef enum actionType { BLE_BUTTON, BLE_ACCEL } actionType_t;

typedef struct {
	actionType_t type;

	// button specific data
	uint8_t btnNumber;
	bool pressed;

	// accelerometer specific data
	float x;
	float y;
	float z;
} controllerAction_t;

void controller_init();

void controller_queueAction(controllerAction_t action);
void controller_process();

bool controller_leftPressed();
bool controller_rightPressed();

#endif /* CONTROLLER_H_ */
