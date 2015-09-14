#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>
#include <stdio.h>

#define MAX_SECONDS 60
#define MAX_MINUTES 60
#define MAX_HOURS 	24

// increments the clock, handling hours, minute, second rollovers
void incrementClock();

// increment/decrement individual time units
uint32_t incrementSeconds();
uint32_t incrementMinutes();
uint32_t incrementHours();
void decrementSeconds();
void decrementMinutes();
void decrementHours();

// Get the current time from the clock
void getClock(uint32_t *s, uint32_t *m, uint32_t *h);

#endif
