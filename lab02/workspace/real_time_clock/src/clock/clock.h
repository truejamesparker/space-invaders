#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>
#include <stdio.h>

#define MAX_SECONDS 60
#define MAX_MINUTES 60
#define MAX_HOURS 23

void incrementClock();
void getClock(uint32_t *s, uint32_t *m, uint32_t *h);

#endif
