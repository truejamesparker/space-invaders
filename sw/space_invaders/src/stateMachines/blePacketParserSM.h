#ifndef BLEPACKETPARSERSM_H_
#define BLEPACKETPARSERSM_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../ble/ble.h"
#include "../controller/controller.h"

#define PACKET_ACC_LEN                  (15)
#define PACKET_GYRO_LEN                 (15)
#define PACKET_MAG_LEN                  (15)
#define PACKET_QUAT_LEN                 (19)
#define PACKET_BUTTON_LEN               (5)
#define PACKET_COLOR_LEN                (6)
#define PACKET_LOCATION_LEN             (15)

#define READ_BUFF_LEN					(20) // this is limited by the Nordic GATT Service

#define PACKET_PARSER_TIMEOUT 			5000 // loop iterations

#define SM_PERIOD_BLE_PACKET_PARSER_MS		60

void blePacketParserSM_tick();

#endif /* BLEPACKETPARSERSM_H_ */
