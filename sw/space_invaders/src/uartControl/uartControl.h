#ifndef UARTCONTROL_H_
#define UARTCONTROL_H_

#include <stdio.h>

#define ASCII_0	48
#define ASCII_3 51

// pass a char key in and the correct
// action is decoded and carried out.
void uartControl_handle(char key);


#endif /* UARTCONTROL_H_ */
