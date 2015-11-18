#include <stdio.h>
#include <string.h>

#include "platform.h"
#include "xparameters.h"
#include "xuartlite.h"
#include "interrupts.h"

#include "BLEDriver/BLE.h"

void print(char *str);

#define READ_BUFF_LEN	50

char packetbuffer[READ_BUFF_LEN+1];

uint16_t readPacket(uint16_t timeout);

int main() {
    init_platform();

    ble_init();

    print("*************** BLE Test *****************\n\r\n\r");

//    while(1) {
//    	if (ble_available()) {
//    		// get the stuff from the BLE buffer
//    		char buffer[BLE_UART_BUFF_SIZE];
//    		ble_read(buffer, BLE_UART_BUFF_SIZE);
//
//    		// print
//    		xil_printf("Got something: %s\r\n", buffer);
//    	}
//    }
    while (1) {
    	if (readPacket(5000)) {
    		xil_printf("Got something: %s\r\n", packetbuffer);
    	}
    }

    cleanup_platform();

    return 0;
}

uint16_t readPacket(uint16_t timeout) {
	uint16_t origtimeout = timeout;
	uint16_t replyidx = 0;

	memset(packetbuffer, 0, READ_BUFF_LEN);

	while (timeout--) {
		if (replyidx >= READ_BUFF_LEN) break;
//		if ((packetbuffer[1] == 'A') && (replyidx == PACKET_ACC_LEN))
//		  break;
//		if ((packetbuffer[1] == 'G') && (replyidx == PACKET_GYRO_LEN))
//		  break;
//		if ((packetbuffer[1] == 'M') && (replyidx == PACKET_MAG_LEN))
//		  break;
//		if ((packetbuffer[1] == 'Q') && (replyidx == PACKET_QUAT_LEN))
//		  break;
//		if ((packetbuffer[1] == 'B') && (replyidx == PACKET_BUTTON_LEN))
//		  break;
//		if ((packetbuffer[1] == 'C') && (replyidx == PACKET_COLOR_LEN))
//		  break;
//		if ((packetbuffer[1] == 'L') && (replyidx == PACKET_LOCATION_LEN))
//		  break;

		while (ble_available()) {
		  char msg[BLE_UART_BUFF_SIZE];
		  ble_read(msg, BLE_UART_BUFF_SIZE);
	//	  if (c == '!') {
	//		replyidx = 0;
	//	  }
		  uint32_t i = 0;

		  for (i=0; i<BLE_UART_BUFF_SIZE; i++) {
			  if (msg[i] == 0) break;
			  packetbuffer[replyidx] = msg[i];
			  replyidx++;
		  }
		  timeout = origtimeout;
		}
	}

	packetbuffer[replyidx] = '\0';

	return replyidx;
}
