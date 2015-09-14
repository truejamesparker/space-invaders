#include "debouncer.h"

// button masks
#define BTN_MIN_MASK 	0x01
#define BTN_S_MASK 		0x02
#define BTN_DOWN_MASK 	0x04
#define BTN_HR_MASK 	0x08
#define BTN_UP_MASK 	0x10

#define BTN_TIME_MASK	(BTN_HR_MASK | BTN_MIN_MASK | BTN_S_MASK)
#define BTN_INC_MASK	(BTN_UP_MASK | BTN_DOWN_MASK)

#define MAX_DEBOUNCE	5
#define AUTO_DEBOUNCE	100
#define FAST_COUNT_MAX	20

static volatile uint32_t oldButtonStates = 0;
static volatile uint32_t debounced = 1;

static volatile uint8_t bouncer_counter = 0;
static volatile uint32_t auto_counter = 0;
static volatile uint8_t inc = 0;
static volatile uint8_t fast_count = 0;
static volatile uint8_t manual = 0;
static volatile uint8_t bounce_enable = 0;

static volatile uint32_t time_pressed;
static volatile uint32_t updown_pressed;

static void inc_time();

// ----------------------------------------------------------------------------

void tick_bouncer(){
	auto_counter++;
	if(!debounced){
		bouncer_counter++;
		if(bouncer_counter == MAX_DEBOUNCE){
			debounced = 1;
			manual = 1;
			if(inc) inc_time();
		}
	} else if(auto_counter > AUTO_DEBOUNCE && inc){
		fast_count++;
		if(fast_count == FAST_COUNT_MAX){
			fast_count = 0;
			inc_time();
		}
	}
}

// ----------------------------------------------------------------------------

uint8_t bouncer(uint32_t currentButtonStates){
	oldButtonStates = currentButtonStates;
	time_pressed = currentButtonStates & BTN_TIME_MASK;
	updown_pressed = currentButtonStates & BTN_INC_MASK;
	inc = time_pressed && updown_pressed;
	bouncer_counter = 0;
	auto_counter = 0;
	debounced = 0;
	manual = 0;
	bounce_enable = 1;
	return (updown_pressed) ? 1 : 0;
}

// ----------------------------------------------------------------------------

uint8_t in_manual(){
	return manual;
}

// ----------------------------------------------------------------------------
// Private Methods
// ----------------------------------------------------------------------------

void inc_time(){
	if (oldButtonStates & BTN_UP_MASK) {
		if (oldButtonStates & BTN_HR_MASK){
			incrementHours();
			}
		if(oldButtonStates & BTN_MIN_MASK){
			incrementMinutes();
		}
		if(oldButtonStates & BTN_S_MASK){
			incrementSeconds();
		}
	}
	if (oldButtonStates & BTN_DOWN_MASK){
		if (oldButtonStates & BTN_HR_MASK){
			decrementHours();
		}
		if(oldButtonStates & BTN_MIN_MASK){
			decrementMinutes();
		}
		if(oldButtonStates & BTN_S_MASK){
			decrementSeconds();
		}
	}
}
