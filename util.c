/*  
    util.c
    Contains utility functions used to help other functions
    This file written 2021 by Kalle Elmdahl
    Some parts are original code written by F Lundevall and Axel Isaksson

    For copyright and licensing, see file COPYING 
*/

#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

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

/* Add delay (not efficient) */
void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

/* Send info to display */
uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}
