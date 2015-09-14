#include "clock.h"
#include <stdio.h>

static uint32_t seconds = 0;
static uint32_t minutes = 0;
static uint32_t hours = 0;
static uint32_t enabled = 1;

void incrementClock() {
	if (!incrementSeconds()) {
		if (!incrementMinutes()) {
			incrementHours();
		}
	}
}

// ----------------------------------------------------------------------------

void getClock(uint32_t *s, uint32_t *m, uint32_t *h) {
	*s = seconds;
	*m = minutes;
	*h = hours;
}

// ----------------------------------------------------------------------------

uint32_t incrementSeconds() {
	if (++seconds == MAX_SECONDS) {
		seconds = 0;
	}
	return seconds;
}

// ----------------------------------------------------------------------------

void decrementSeconds() {
	if (--seconds > MAX_SECONDS) {
		seconds = MAX_SECONDS - 1;
	}
}

// ----------------------------------------------------------------------------

uint32_t incrementMinutes() {
	if (++minutes == MAX_MINUTES) {
		minutes = 0;
	}
	return minutes;
}

// ----------------------------------------------------------------------------

void decrementMinutes() {
	if (--minutes > MAX_MINUTES) {
		minutes = MAX_MINUTES - 1;
	}
}

// ----------------------------------------------------------------------------

uint32_t incrementHours() {
	if (++hours == MAX_HOURS) {
		hours = 0;
	}
	return hours;
}

// ----------------------------------------------------------------------------

void decrementHours() {
	if (--hours > MAX_HOURS) {
		hours = MAX_HOURS - 1;
	}
}

// ----------------------------------------------------------------------------

uint32_t clock_enabled(){
	return enabled;
}

// ----------------------------------------------------------------------------

void clock_disable(){
	enabled = 0;
}

// ----------------------------------------------------------------------------

void clock_enable(){
	enabled = 1;
}
