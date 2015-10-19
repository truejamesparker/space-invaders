#ifndef TASKCONTROL_H_
#define TASKCONTROL_H_

#include <stdio.h>
#include <stdint.h>

#include "../stateMachines/alienBlockSM.h"
#include "../stateMachines/screenRefreshSM.h"
#include "../stateMachines/tankSM.h"
#include "../stateMachines/missileSM.h"
#include "../stateMachines/spaceshipSM.h"
#include "../stateMachines/gamePlaySM.h"

#define TC_TIMER_PERIOD_MS 	10 	// how often does the FIT expire?
#define TC_SM_COUNT 		6	// Pretty self explanatory, eh?

// An array of these are created to handle when to tick SMs
typedef struct {
	uint32_t period;
	uint32_t elapsedTime;
	void (*TickFn)(void);
} task_t;

// Set up all the tasks needed for this project
void taskControl_init();

// Tick the tasks (i.e., the FIT timer expired
// and it's time to tick all the state machines)
void taskControl_tick();


#endif /* TASKCONTROL_H_ */
