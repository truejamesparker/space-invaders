#include "blePacketParserSM.h"

static char packetbuffer[READ_BUFF_LEN+1];

uint16_t readPacket(uint16_t timeout);
float parsefloat(char *buffer);

// ----------------------------------------------------------------------------

void blePacketParserSM_tick() {
	if (readPacket(PACKET_PARSER_TIMEOUT)) {

		// Buttons
		if (packetbuffer[1] == 'B') {
			// since it's a char, we can subtract ASCII 0
			// to get the numerical value of the button
			uint8_t btnNum = packetbuffer[2] - '0';
			uint8_t pressed = packetbuffer[3] - '0';

			// create a button controller action
			controllerAction_t action = {
					.type = BLE_BUTTON,
					.btnNumber = btnNum,
					.pressed = pressed
			};

			// queue the action up for the controllerSM to process
			controller_queueAction(action);
		}

		// Accelerometer
		if (packetbuffer[1] == 'A') {
			float x, y, z;

			// take the bytes from BLE and make them floats
			x = parsefloat(packetbuffer+2);
//			xil_printf(" ");
			y = parsefloat(packetbuffer+6);
//			xil_printf(" ");
			z = parsefloat(packetbuffer+10);

//			xil_printf("\r\n");

			// create an accelerometer action
			controllerAction_t action = {
					.type = BLE_ACCEL,
					.x = x, .y = y, .z = z
			};

			// queue the action up for the controllerSM to process
			controller_queueAction(action);
		}


	}
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

// ----------------------------------------------------------------------------
// Private Helper Methods
// ----------------------------------------------------------------------------

float parsefloat(char *buffer) {
	// There seems to be an endian mismatch...
	uint32_t tmp = ((uint8_t)buffer[0]) << 0;
	tmp = tmp | ((uint8_t)buffer[1]) << 8;
	tmp = tmp | ((uint8_t)buffer[2]) << 16;
	tmp = tmp | ((uint8_t)buffer[3]) << 24;

//	xil_printf("%x", tmp);

	float f = *(float *)&tmp;
	return f;
}
