#include "debouncer.h"

static volatile uint32_t oldButtonStates = 0;
static volatile uint32_t debounced = 1;

static volatile uint8_t bouncer_counter = 0;
static volatile uint32_t auto_counter = 0;
static volatile uint8_t inc = 0;
static volatile uint8_t fast_count = 0;
static volatile uint8_t auto_mode = 0;

static volatile uint32_t time_pressed;
static volatile uint32_t updown_pressed;

static void inc_time();

// ----------------------------------------------------------------------------

void tick_bouncer(){
	// keep track of how many interrupts have happened
	// so we know when to enable auto-increment mode
	auto_counter++;

	// if I haven't already been debounced, then debounce me!
	if(!debounced){
		bouncer_counter++;
		if (bouncer_counter == MAX_DEBOUNCE) {
			// now that I'm debounced, let the world know.
			debounced = 1;

			// also, I can now go into the auto-increment mode
			auto_mode = 1;

			// also, if a time button and up/down button is pressed,
			// change time.
			if (inc) inc_time();
		}
	} else if (auto_counter > ONE_SECOND && inc) {
		// because I'm already debounced, now check if the button
		// has been held for longer than a second. If it has, and
		// the appropriate buttons are pressed, enable the fast count.
		fast_count++;
		if(fast_count == FAST_COUNT_MAX){
			fast_count = 0;
			inc_time();
		}
	}
}

// ----------------------------------------------------------------------------

uint8_t bouncer(uint32_t currentButtonStates){
	// capture the button states to use after buttons have been debounced
	oldButtonStates = currentButtonStates;

	// Decide if a time button is being pressed...
	time_pressed = currentButtonStates & BTN_TIME_MASK;
	// ...or the up/down button.
	updown_pressed = currentButtonStates & BTN_INC_MASK;

	// if a time button and an up/down is pressed,
	// then we are okay to change the time.
	inc = time_pressed && updown_pressed;

	// reset our counters and modes
	bouncer_counter = 0;
	auto_counter = 0;
	debounced = 0;
	auto_mode = 0;

	// Let the caller know to start debouncing,
	// but only if it was an up/down button.
	// (nothing happens unless an up/down button is pressed)
	return (updown_pressed) ? 1 : 0;
}

// ----------------------------------------------------------------------------

uint8_t in_auto_increment_mode() {
	return auto_mode;
}

// ----------------------------------------------------------------------------
// Private Methods
// ----------------------------------------------------------------------------

void inc_time(){
	// increment/decrement the appropriate time unit
	// according to the pressed buttons

	if (oldButtonStates & BTN_UP_MASK) {
		if (oldButtonStates & BTN_HR_MASK)  incrementHours();
		if (oldButtonStates & BTN_MIN_MASK) incrementMinutes();
		if (oldButtonStates & BTN_S_MASK)   incrementSeconds();
	}

	if (oldButtonStates & BTN_DOWN_MASK){
		if (oldButtonStates & BTN_HR_MASK)  decrementHours();
		if (oldButtonStates & BTN_MIN_MASK) decrementMinutes();
		if (oldButtonStates & BTN_S_MASK)   decrementSeconds();
	}
}
