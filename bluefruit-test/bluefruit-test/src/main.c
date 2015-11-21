#include <stdio.h>
#include <string.h>

#include "platform.h"
#include "xparameters.h"
#include "xuartlite.h"
#include "interrupts.h"

#include "BLEDriver/BLE.h"

void print(char *str);

#define PACKET_ACC_LEN                  (15)
#define PACKET_GYRO_LEN                 (15)
#define PACKET_MAG_LEN                  (15)
#define PACKET_QUAT_LEN                 (19)
#define PACKET_BUTTON_LEN               (5)
#define PACKET_COLOR_LEN                (6)
#define PACKET_LOCATION_LEN             (15)

#define READ_BUFF_LEN	20 // this is limited by the Nordic GATT Service

char packetbuffer[READ_BUFF_LEN+1];

uint16_t readPacket(uint16_t timeout);
float parsefloat(char *buffer);
void printFloat(float f);

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
    	if (readPacket(10000)) {
//    		xil_printf("Got something: %s\r\n", packetbuffer);


			// Buttons
			if (packetbuffer[1] == 'B') {
				uint8_t buttnum = packetbuffer[2] - '0';
				uint8_t pressed = packetbuffer[3] - '0';
				printf("Button %d", buttnum);
				if (pressed) xil_printf(" pressed\r\n");
				else 		 xil_printf(" released\r\n");
			}

			// Accelerometer
			if (packetbuffer[1] == 'A') {
				float x, y, z;
				x = 1.1f;
				y = 2.2f;
				z = 3.3f;
				x = parsefloat(packetbuffer+2);
				y = parsefloat(packetbuffer+6);
				z = parsefloat(packetbuffer+10);
				xil_printf("Accel\tx: "); printFloat(x);
				xil_printf("\ty:"); printFloat(y);
				xil_printf("\tz:"); printFloat(z);
				xil_printf("\r\n");
			}

    	}
    }

    cleanup_platform();

    return 0;
}

// ----------------------------------------------------------------------------

void printFloat(float f) {
	uint32_t left = (int)f;
	xil_printf("%d.%d", left, (f-(float)left)*1000);
}

// ----------------------------------------------------------------------------

float parsefloat(char *buffer) {
  float f = ((float *)buffer)[0];
  return f;
}

// ----------------------------------------------------------------------------

uint16_t readPacket(uint16_t timeout) {
	uint16_t origtimeout = timeout;
	uint16_t replyidx = 0;

	memset(packetbuffer, 0, READ_BUFF_LEN);

	while (timeout--) {
		if (replyidx >= READ_BUFF_LEN) break;
		if ((packetbuffer[1] == 'A') && (replyidx == PACKET_ACC_LEN))
		  break;
		if ((packetbuffer[1] == 'G') && (replyidx == PACKET_GYRO_LEN))
		  break;
		if ((packetbuffer[1] == 'M') && (replyidx == PACKET_MAG_LEN))
		  break;
		if ((packetbuffer[1] == 'Q') && (replyidx == PACKET_QUAT_LEN))
		  break;
		if ((packetbuffer[1] == 'B') && (replyidx == PACKET_BUTTON_LEN))
		  break;
		if ((packetbuffer[1] == 'C') && (replyidx == PACKET_COLOR_LEN))
		  break;
		if ((packetbuffer[1] == 'L') && (replyidx == PACKET_LOCATION_LEN))
		  break;

		while (ble_available()) {
		  char c = ble_read();
		  if (c == '!') {
			replyidx = 0;
		  }
		  packetbuffer[replyidx] = c;
		  replyidx++;
		  timeout = origtimeout;
		}
	}

	packetbuffer[replyidx] = '\0';

	return replyidx;
}
