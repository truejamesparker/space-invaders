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

void print(char *str);

int main()
{
    init_platform();

    xil_printf("Hello World\n\r");
    uint32_t before, after;
    before = DMA_CTRL_mReadSlaveReg0(XPAR_DMA_CTRL_0_BASEADDR, 0);
    xil_printf("%x\n\r", before);
    DMA_CTRL_mWriteSlaveReg0(XPAR_DMA_CTRL_0_BASEADDR, 0, 0xDEADBEEF);
    after = DMA_CTRL_mReadSlaveReg0(XPAR_DMA_CTRL_0_BASEADDR, 0);
    xil_printf("%x\n\r", after);

    cleanup_platform();

    return 0;
}
