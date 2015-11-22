#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../ble/ble.h"

#define PACKET_ACC_LEN                  (15)
#define PACKET_GYRO_LEN                 (15)
#define PACKET_MAG_LEN                  (15)
#define PACKET_QUAT_LEN                 (19)
#define PACKET_BUTTON_LEN               (5)
#define PACKET_COLOR_LEN                (6)
#define PACKET_LOCATION_LEN             (15)

#define READ_BUFF_LEN					(20) // this is limited by the Nordic GATT Service

#define CONTROLLER_PACKET_PARSER_TIMEOUT 5000 // loop iterations

controller_figureOutWhichDirectionToMoveThereIsProbablyABetterWayToDoThis();

bool controller_leftPressed();
bool controller_rightPressed();

#endif /* CONTROLLER_H_ */
