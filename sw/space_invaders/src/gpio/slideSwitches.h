#ifndef SLIDESWITCHES_H_
#define SLIDESWITCHES_H_

#include <stdbool.h>
#include <stdint.h>

#include "xparameters.h"
#include "xgpio.h"

#define SW_CREATE_MASK(sw) (0x01 << sw)

// Define different sliders to be different actions
#define SW_PAUSE		(0x00)

// Setup the switches in HW
void slideSwitches_init();

// Public functions to make life easy
bool slideSwitches_isOn(uint8_t sw);

#endif /* SLIDESWITCHES_H_ */
