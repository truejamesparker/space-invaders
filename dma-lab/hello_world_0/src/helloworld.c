/*
 * Copyright (c) 2009 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * helloworld.c: simple test application
 */

#include <stdio.h>
#include "platform.h"
#include "dma_ctrl.h"
#include "xparameters.h"
#include "stdint.h"
#include "mb_interface.h"   // provides the microblaze interrupt enables, etc.
#include "xintc_l.h"        // Provides handy macros for the interrupt controller.

volatile uint32_t dest[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
volatile uint32_t src[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13};

void dma_interrupt_handler(){
	xil_printf("done!\n\r");
	int i;
	for(i=0; i<13; i++){
		xil_printf("After: %d\n\r", dest[i]);
	}

}

void interrupt_handler_dispatcher(void* ptr) {
	int intc_status = XIntc_GetIntrStatus(XPAR_INTC_0_BASEADDR);

	// Check the FIT interrupt first.
	if (intc_status & XPAR_DMA_CTRL_0_INTERRUPT_MASK){
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_DMA_CTRL_0_INTERRUPT_MASK);
		dma_interrupt_handler();
	}
}

int main()
{
    init_platform();
    cleanup_platform();

    microblaze_register_handler(interrupt_handler_dispatcher, NULL);
	XIntc_EnableIntr(XPAR_INTC_0_BASEADDR, XPAR_DMA_CTRL_0_INTERRUPT_MASK);
	XIntc_MasterEnable(XPAR_INTC_0_BASEADDR);
   microblaze_enable_interrupts();

	int i;
	for(i=0; i<13; i++){
		xil_printf("Before: %d\n\r", dest[i]);
	}
    DMA_CTRL_transfer(XPAR_DMA_CTRL_0_BASEADDR, &src, &dest, 4*13);

    while(1);



    return 0;
}
