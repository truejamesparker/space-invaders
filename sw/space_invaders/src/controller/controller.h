#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../ble/ble.h"
#include "../queue/queue.h"
#include "../elements/tank.h"
#include "../elements/missiles.h"

#define PACKET_ACC_LEN                  (15)
#define PACKET_GYRO_LEN                 (15)
#define PACKET_MAG_LEN                  (15)
#define PACKET_QUAT_LEN                 (19)
#define PACKET_BUTTON_LEN               (5)
#define PACKET_COLOR_LEN                (6)
#define PACKET_LOCATION_LEN             (15)

#define READ_BUFF_LEN					(20) // this is limited by the Nordic GATT Service

#define CONTROLLER_PACKET_PARSER_TIMEOUT 5000 // loop iterations

#define CONTROLLER_QUEUE_LENGTH			64

#define CONTROLLER_BTN_LEFT				7
#define CONTROLLER_BTN_RIGHT			8
#define CONTROLLER_BTN_FIRE				1

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
bool controller_process();

bool controller_leftPressed();
bool controller_rightPressed();

#endif /* CONTROLLER_H_ */
