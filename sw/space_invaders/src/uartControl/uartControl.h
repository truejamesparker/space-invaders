#ifndef UARTCONTROL_H_
#define UARTCONTROL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../elements/aliens.h"
#include "../elements/tank.h"
#include "../elements/bunkers.h"
#include "../elements/missiles.h"

#define ASCII_0	48
#define ASCII_3 51
#define ASCII_9 57

// pass a char key in and the correct
// action is decoded and carried out.
void uartControl_handle(char key);


#endif /* UARTCONTROL_H_ */
