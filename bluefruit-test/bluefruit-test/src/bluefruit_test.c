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
#include "xparameters.h"
#include "xuartlite.h"
#include "interrupts.h"

#define TEST_BUFFER_SIZE 16

XUartLite uartlite;

uint8_t data_buffer[TEST_BUFFER_SIZE];
uint8_t send_buffer[TEST_BUFFER_SIZE] = "hello!\n";

void print(char *str);
void clear_buffer(uint8_t *buffer, uint8_t len);

void uart_handler(){
	XUartLite_InterruptHandler(&uartlite);
}

void print_buffer(){
	xil_printf("%s", data_buffer);
	clear_buffer(data_buffer, TEST_BUFFER_SIZE);
}

void clear_buffer(uint8_t *buffer, uint8_t len){
	int i;
	for(i=0; i<len; i++){
		buffer[i] = 0;
	}
}

int main()
{


    init_platform();
    interrupts_init();
    interrupts_register_handler(INTS_UART, uart_handler);

    XUartLite_Initialize(&uartlite, XPAR_AXI_UARTLITE_0_DEVICE_ID);
    XUartLite_ResetFifos(&uartlite);
    XUartLite_SetRecvHandler(&uartlite, uart_handler, NULL);
    XUartLite_EnableInterrupt(&uartlite);



    print("Hello World\n\r");
    while(1);

//    while(1){
//
//    	    uint16_t SentCount = XUartLite_Send(&uartlite, send_buffer, TEST_BUFFER_SIZE);
//    	    if (SentCount != TEST_BUFFER_SIZE)
//    	    {
//    	    	xil_printf("failed to send\n\r");
//    	        return XST_FAILURE;
//    	    }
//
//    	    /*
//    	     * Wait while the UartLite is sending the data so that we are guaranteed
//    	     * to get the data the 1st time we call receive, otherwise this function
//    	     * may enter receive before the data has arrived.
//    	     */
//    	    while (XUartLite_IsSending(&uartlite));
//
//
//    	    while(!XUartLite_Recv(&uartlite, data_buffer, TEST_BUFFER_SIZE));
//    	    xil_printf("%s", data_buffer);
//    	    XUartLite_ResetFifos(&uartlite);
//
//
//    }

    cleanup_platform();

    return 0;
}

///* $Id: xuartlite_polled_example.c,v 1.1.2.1 2008/02/12 12:42:02 svemula Exp $ */
///*****************************************************************************
//*
//*       XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"
//*       AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND
//*       SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,
//*       OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,
//*       APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION
//*       THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,
//*       AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE
//*       FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY
//*       WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE
//*       IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR
//*       REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF
//*       INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
//*       FOR A PARTICULAR PURPOSE.
//*
//*       (c) Copyright 2002-2008 Xilinx Inc.
//*       All rights reserved.
//*
//*******************************************************************************/
///******************************************************************************/
///**
//*
//* @file xuartlite_polled_example.c
//*
//* This file contains a design example using the UartLite driver (XUartLite) and
//* hardware device using the polled mode.
//*
//* @note
//*
//* The user must provide a physical loopback such that data which is
//* transmitted will be received.
//*
//* MODIFICATION HISTORY:
//* <pre>
//* Ver   Who  Date     Changes
//* ----- ---- -------- -----------------------------------------------
//* 1.00a jhl  02/13/02 First release
//* 1.00a sv   06/13/05 Minor changes to comply to Doxygen and coding guidelines
//* </pre>
//******************************************************************************/
//
///***************************** Include Files *********************************/
//
//#include "xparameters.h"
//#include "xstatus.h"
//#include "xuartlite.h"
//
//
///************************** Constant Definitions *****************************/
//
///*
// * The following constants map to the XPAR parameters created in the
// * xparameters.h file. They are defined here such that a user can easily
// * change all the needed parameters in one place.
// */
//#define UARTLITE_DEVICE_ID          XPAR_UARTLITE_0_DEVICE_ID
//
///*
// * The following constant controls the length of the buffers to be sent
// * and received with the UartLite, this constant must be 16 bytes or less since
// * this is a single threaded non-interrupt driven example such that the
// * entire buffer will fit into the transmit and receive FIFOs of the UartLite.
// */
//#define TEST_BUFFER_SIZE 16
//
///**************************** Type Definitions *******************************/
//
//
///***************** Macros (Inline Functions) Definitions *********************/
//
//
///************************** Function Prototypes ******************************/
//
//XStatus UartLitePolledExample(Xuint16 DeviceId);
//
///************************** Variable Definitions *****************************/
//
//XUartLite UartLite;                    /* Instance of the UartLite Device */
//
///*
// * The following buffers are used in this example to send and receive data
// * with the UartLite.
// */
//Xuint8 SendBuffer[TEST_BUFFER_SIZE];    /* Buffer for Transmitting Data */
//Xuint8 RecvBuffer[TEST_BUFFER_SIZE];    /* Buffer for Receiving Data */
//
//
///*****************************************************************************/
///**
//*
//* Main function to call the Uartlite polled example.
//*
//* @param    None.
//*
//* @return   XST_SUCCESS if successful, otherwise XST_FAILURE.
//*
//* @note     None.
//*
//******************************************************************************/
//int main(void)
//{
//    XStatus Status;
//
//    /*
//     * Run the UartLite polled example, specify the Device ID that is
//     * generated in xparameters.h
//     */
//    Status = UartLitePolledExample(UARTLITE_DEVICE_ID);
//    if (Status != XST_SUCCESS)
//    {
//    	xil_printf("failure\n\r");
//        return XST_FAILURE;
//    }
//    xil_printf("success\n\r");
//    return XST_SUCCESS;
//
//}
//
//
///****************************************************************************/
///**
//* This function does a minimal test on the UartLite device and driver as a
//* design example. The purpose of this function is to illustrate
//* how to use the XUartLite component.
//*
//* This function sends data and expects to receive the data thru the UartLite
//* such that a  physical loopback must be done with the transmit and receive
//* signals of the UartLite.
//*
//* This function polls the UartLite and does not require the use of interrupts.
//*
//* @param    DeviceId is the Device ID of the UartLite and is the
//*           XPAR_<uartlite_instance>_DEVICE_ID value from xparameters.h.
//*
//* @return   XST_SUCCESS if successful, XST_FAILURE if unsuccessful.
//*
//*
//* @note
//*
//* This function calls the UartLite driver functions in a blocking mode such that
//* if the transmit data does not loopback to the receive, this function may
//* not return.
//*
//****************************************************************************/
//XStatus UartLitePolledExample(Xuint16 DeviceId)
//{
//    XStatus Status;
//    unsigned int SentCount;
//    unsigned int ReceivedCount;
//    int Index;
//
//    /*
//     * Initialize the UartLite driver so that it is ready to use.
//     */
//    Status = XUartLite_Initialize(&UartLite, DeviceId);
//    if (Status != XST_SUCCESS)
//    {
//    	xil_printf("failed init\n\r");
//        return XST_FAILURE;
//    }
//
//    /*
//     * Perform a self-test to ensure that the hardware was built correctly.
//     */
//    Status = XUartLite_SelfTest(&UartLite);
//    if (Status != XST_SUCCESS)
//    {
//    	xil_printf("failed selfTest\n\r");
//        return XST_FAILURE;
//    }
//
//    /*
//     * Initialize the send buffer bytes with a pattern to send and the
//     * the receive buffer bytes to zero.
//     */
//    for (Index = 0; Index < TEST_BUFFER_SIZE; Index++)
//    {
//        SendBuffer[Index] = Index;
//        RecvBuffer[Index] = 0;
//    }
//
//    /*
//     * Send the buffer through the UartLite waiting til the data can be sent
//     * (block), if the specified number of bytes was not sent successfully,
//     * then an error occurred.
//     */
//    SentCount = XUartLite_Send(&UartLite, SendBuffer, TEST_BUFFER_SIZE);
//    if (SentCount != TEST_BUFFER_SIZE)
//    {
//    	xil_printf("failed to send\n\r");
//        return XST_FAILURE;
//    }
//
//    /*
//     * Wait while the UartLite is sending the data so that we are guaranteed
//     * to get the data the 1st time we call receive, otherwise this function
//     * may enter receive before the data has arrived.
//     */
//    while (XUartLite_IsSending(&UartLite))
//    {
//    }
//
//    /*
//     * Receive the buffer from the UartLite waiting til there's data by (block),
//     * if the specified number of bytes was not received successfully, then
//     * an error occurred.
//     */
//
//    ReceivedCount = XUartLite_Recv(&UartLite, RecvBuffer, TEST_BUFFER_SIZE);
//    if (ReceivedCount != TEST_BUFFER_SIZE)
//    {
//    	xil_printf("failed to rec\n\r");
//        return XST_FAILURE;
//    }
//
//    /*
//     * Check the receive buffer data against the send buffer and verify the
//     * data was correctly received.
//     */
//    for (Index = 0; Index < TEST_BUFFER_SIZE; Index++)
//    {
//        if (SendBuffer[Index] != RecvBuffer[Index])
//        {
//        	xil_printf("data was different\n\r");
//            return XST_FAILURE;
//        }
//    }
//
//    return XST_SUCCESS;
//}
