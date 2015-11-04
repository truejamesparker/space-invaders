/*
 * pit.c
 *
 *  Created on: Nov 3, 2015
 *      Author: superman
 */

#include "pit.h"

void pit_init(){
	Xil_Out32((XPAR_PIT_0_BASEADDR) + PIT_CTRL_REG_OFFSET, PIT_CTRL_RESET_VALUE);
	Xil_Out32((XPAR_PIT_0_BASEADDR) + PIT_DATA_REG_OFFSET, COUNTER_RESET_VALUE);
}

void pit_enable_count(){
	uint32_t cntr_val = *(uint32_t *)(XPAR_PIT_0_BASEADDR + PIT_CTRL_REG_OFFSET);
	cntr_val = cntr_val | PIT_COUNT_EN_MASK;
	Xil_Out32((XPAR_PIT_0_BASEADDR) + PIT_CTRL_REG_OFFSET, cntr_val);
}

void pit_disable_count(){
	uint32_t cntr_val = *(uint32_t *)(XPAR_PIT_0_BASEADDR + PIT_CTRL_REG_OFFSET);
	cntr_val = cntr_val & ~PIT_COUNT_EN_MASK;
	Xil_Out32((XPAR_PIT_0_BASEADDR) + PIT_CTRL_REG_OFFSET, cntr_val);
}

void pit_enable_interrupts(){
	uint32_t cntr_val = *(uint32_t *)(XPAR_PIT_0_BASEADDR + PIT_CTRL_REG_OFFSET);
	cntr_val = cntr_val | PIT_INT_EN_MASK;
	Xil_Out32((XPAR_PIT_0_BASEADDR) + PIT_CTRL_REG_OFFSET, cntr_val);
}

void pit_disable_interrupts(){
	uint32_t cntr_val = *(uint32_t *)(XPAR_PIT_0_BASEADDR + PIT_CTRL_REG_OFFSET);
	cntr_val = cntr_val & ~PIT_INT_EN_MASK;
	Xil_Out32((XPAR_PIT_0_BASEADDR) + PIT_CTRL_REG_OFFSET, cntr_val);
}

void pit_enable_load(){
	uint32_t cntr_val = *(uint32_t *)(XPAR_PIT_0_BASEADDR + PIT_CTRL_REG_OFFSET);
	cntr_val = cntr_val | PIT_LOAD_EN_MASK;
	Xil_Out32((XPAR_PIT_0_BASEADDR) + PIT_CTRL_REG_OFFSET, cntr_val);
}

void pit_disable_load(){
	uint32_t cntr_val = *(uint32_t *)(XPAR_PIT_0_BASEADDR + PIT_CTRL_REG_OFFSET);
	cntr_val = cntr_val & ~PIT_LOAD_EN_MASK;
	Xil_Out32((XPAR_PIT_0_BASEADDR) + PIT_CTRL_REG_OFFSET, cntr_val);
}

void pit_load_value(uint32_t counter_val){
	Xil_Out32((XPAR_PIT_0_BASEADDR) + PIT_DATA_REG_OFFSET, counter_val);
}

