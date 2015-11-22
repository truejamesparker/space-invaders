#ifndef BLESM_H_
#define BLESM_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../ble/ble.h"

#define SM_PERIOD_BLE_MS		60

void bleSM_tick();

#endif /* BLESM_H_ */
