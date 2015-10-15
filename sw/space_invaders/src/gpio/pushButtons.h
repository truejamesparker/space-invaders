#ifndef PUSHBUTTONS_H_
#define PUSHBUTTONS_H_

#include <stdbool.h>

#include "xparameters.h"
#include "xgpio.h"

#define BTN_LEFT_MASK	0x08
#define BTN_RIGHT_MASK	0x02
#define BTN_DOWN_MASK	0x04
#define BTN_UP_MASK		0x10
#define BTN_CENTER_MASK	0x01
#define BTN_ANY_MASK	0xFF

// Setup the PBs in HW
void pushButtons_init();

// Public functions to make life easy
bool pushButtons_leftPressed();
bool pushButtons_rightPressed();
bool pushButtons_downPressed();
bool pushButtons_upPressed();
bool pushButtons_centerPressed();
bool pushButtons_anyPressed();

#endif /* PUSHBUTTONS_H_ */
