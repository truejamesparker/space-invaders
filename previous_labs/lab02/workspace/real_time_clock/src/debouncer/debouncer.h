/*
 * debouncer.h
 *
 *  Created on: Sep 10, 2015
 *      Author: superman
 */

#ifndef DEBOUNCER_H_
#define DEBOUNCER_H_

#include <stdint.h>
#include "../clock/clock.h"

// button masks
#define BTN_MIN_MASK 	0x01
#define BTN_S_MASK 		0x02
#define BTN_DOWN_MASK 	0x04
#define BTN_HR_MASK 	0x08
#define BTN_UP_MASK 	0x10

#define BTN_TIME_MASK	(BTN_HR_MASK | BTN_MIN_MASK | BTN_S_MASK)
#define BTN_INC_MASK	(BTN_UP_MASK | BTN_DOWN_MASK)

// timing constants
#define MAX_DEBOUNCE	5
#define ONE_SECOND		100
#define FAST_COUNT_MAX	20

// Start the button debouncer
uint8_t bouncer(uint32_t newButtonState);

// Returns whether or not we are auto incrementing
uint8_t in_auto_increment_mode();

// Tell the bouncer that an interrupt has occured
// so it can debounce the button
void tick_bouncer();

#endif /* DEBOUNCER_H_ */
