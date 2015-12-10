#ifndef TIMER_H_
#define TIMER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "xtmrctr.h"
#include "xparameters.h"

void timer_init();
void timer_start();
void timer_stop(uint32_t *elapsedTime);

#endif /* TIMER_H_ */
