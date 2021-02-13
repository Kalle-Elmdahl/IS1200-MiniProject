#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

void update_display() {
    uint8_t displayData[4][128];
    int i, j, k;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 128; j++) {
            uint8_t sum = 0;
            for(k = 0; k < 8; k++) sum |= pixels[i*8 + k][j] << k;
            displayData[i][j] = sum;
        }
    }

    for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10);
		DISPLAY_CHANGE_TO_DATA_MODE;

		for(j = 0; j < 128; j++) {
			spi_send_recv(displayData[i][j]);
		}
	}

}