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

uint8_t bouncer(uint32_t newButtonState);
uint8_t in_manual();
void tick_bouncer();

#endif /* DEBOUNCER_H_ */
