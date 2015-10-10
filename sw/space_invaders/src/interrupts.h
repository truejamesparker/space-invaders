#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <stdio.h>
#include <stdint.h>

#include "mb_interface.h"
#include "xintc_l.h"

// Interrupt Types
#define INTS_TIMER	0

void interrupts_init();

void interrupts_register_handler(uint8_t type, void (*func)(void));

#endif /* INTERRUPTS_H_ */
