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
    uint8_t displayData[DISPLAY_ROWS][DISPLAY_WIDTH];
    int i, j, k;
    for(i = 0; i < DISPLAY_ROWS; i++) {
        for(j = 0; j < DISPLAY_WIDTH; j++) {
            uint8_t sum = 0;
            for(k = 0; k < DISPLAY_ROW_HEIGHT; k++) sum |= pixels[i*8 + k][j] << k;
            displayData[i][j] = sum ^ text[i][j]; // add drawn pixels or added text if both are on, the pixel is 0
        }
    }

    for(i = 0; i < DISPLAY_ROWS; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10);
		DISPLAY_CHANGE_TO_DATA_MODE;

		for(j = 0; j < DISPLAY_WIDTH; j++) {
			spi_send_recv(displayData[i][j]);
		}
	}

}

void draw_text(int x, int y, char *s) {
	int i, charx;
	if(y < 0 || y >= DISPLAY_ROWS || !s)
		return;
	
	for(i = x; i < DISPLAY_WIDTH; i++) {
		if(*s) {
            charx = (i - x) % CHAR_WIDTH;
			text[y][i] = font[*s][charx];
            if(charx == CHAR_WIDTH - 1) s++;
		} else
			text[y][i] = 0;
    }
}

void draw_rect(int x, int y, int w, int h) {
    if(x < 0 || y < 0 || w < 0 || h < 0) return;
    if(x + w > DISPLAY_WIDTH || y + h > DISPLAY_HEIGHT) return;
    int i, j;
    for(i = 0; i <= w; i++)
        for(j = 0; j <= h; j++)
            pixels[j + y][i + x] = 1;
}

void clear_pixels() {
    int i, j;
    for(j = 0; j < DISPLAY_WIDTH; j++) {
        for(i = 0; i < DISPLAY_HEIGHT; i++)
            pixels[i][j] = 0;
        for(i = 0; i < DISPLAY_ROWS; i++) {
			text[i][j] = 0;
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