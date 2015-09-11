#include "clock.h"

static uint32_t seconds = 0;
static uint32_t minutes = 0;
static uint32_t hours = 0;

uint32_t incrementSeconds();
uint32_t incrementMinutes();
uint32_t incrementHours();

void incrementClock() {
	if (!incrementSeconds()) {
		if (!incrementMinutes()) {
			incrementHours();
		}
	}
}

void getClock(uint32_t *s, uint32_t *m, uint32_t *h) {
	*s = seconds;
	*m = minutes;
	*h = hours;
}

// ----------------------------
// Private Methods
// ----------------------------

uint32_t incrementSeconds() {
	if (++seconds == MAX_SECONDS) {
		seconds = 0;
	}
	return seconds;
}

uint32_t incrementMinutes() {
	if (++minutes == MAX_MINUTES) {
		minutes = 0;
	}
	return minutes;
}

uint32_t incrementHours() {
	if (++hours == MAX_HOURS) {
		hours = 0;
	}
	return hours;
}
