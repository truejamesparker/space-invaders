#ifndef SCREENCAPTURE_H_
#define SCREENCAPTURE_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "screen.h"

void screenCapture_init();

void screenCapture_hwSave();
void screenCapture_swSave();
void screenCapture_show();

#endif /* SCREENCAPTURE_H_ */
