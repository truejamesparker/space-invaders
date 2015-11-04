/*
 * pit.h
 *
 *  Created on: Nov 3, 2015
 *      Author: superman
 */

#ifndef PIT_H_
#define PIT_H_

#include "xparameters.h"
#include "xil_io.h"
#include <stdio.h>
#include <stdint.h>

#define PIT_CTRL_REG_OFFSET		0x00
#define PIT_DATA_REG_OFFSET		0x04
#define COUNTER_RESET_VALUE		0xFFFFFFFF
#define PIT_CTRL_RESET_VALUE	0x00
#define PIT_COUNT_EN_MASK		0x01
#define PIT_INT_EN_MASK			0x02
#define PIT_LOAD_EN_MASK		0x04

void pit_init();

void pit_enable_count();
void pit_disable_count();

void pit_enable_interrupts();
void pit_disable_interrupts();

void pit_enable_load();
void pit_disable_load();

void pit_load_value(uint32_t counter_val);


#endif /* PIT_H_ */
