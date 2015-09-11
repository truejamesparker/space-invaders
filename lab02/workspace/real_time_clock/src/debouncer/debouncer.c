
#include "debouncer.h"
#include <stdio.h>

uint8_t enable = 0;
uint8_t bouncer_counter = 0;
uint8_t valid_press = 0;

void enable_bouncer() {
	enable = 1;
}

void disable_bouncer() {
	enable = 0;
	bouncer_counter = 0;
}

int bounce_enabled(){
	return enable;
}

void inc_bouncer(){
	if(++bouncer_counter == 5){
		valid_press = 1;
		disable_bouncer();
		xil_printf("debounced\n");
	}
}

int is_valid(){
	return valid_press;
}

