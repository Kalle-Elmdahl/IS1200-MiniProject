/************************************************************

         Very Advanced Snake on Very Small Display

A game by Kalle Elmdahl and Erik Malm, developed in the KTH 
course IS1200 during spring 2021.

~~~~~~~~~~~~~~~~~~~~~~~~~~~ util.c ~~~~~~~~~~~~~~~~~~~~~~~~~~~

util.c contains utility functions used to help other functions.
This file written 2021 by Kalle Elmdahl

************************************************************/

#include <stdint.h>
#include <pic32mx.h>
#include "snake.h"

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

void update_display() {
    int i, j, k, sum;
    for(i = 0; i < DISPLAY_ROWS; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10);
		DISPLAY_CHANGE_TO_DATA_MODE;
        for(j = 0; j < DISPLAY_WIDTH; j++, sum = 0) {
            for(k = 0; k < DISPLAY_ROW_HEIGHT; k++) sum |= pixels[i*8 + k][j] << k;
			spi_send_recv(sum ^ text[i][j]);
        }
    }
}

void draw_text(int x, int y, char *s) {
	if(y < 0 || y >= DISPLAY_ROWS || !s)
		return;
	int i, charx = 0, zeros_in_a_row = 0;

    while(*s) {
        if(*s == 32) { // Space
            x += 4;
        } else {
            while (charx < CHAR_WIDTH) {
                if(!font[*s][charx]) zeros_in_a_row++;
                if(x == DISPLAY_WIDTH || zeros_in_a_row == 2) break;
                text[y][x++] = font[*s][charx++];
            }
        }
        s++;
        zeros_in_a_row = charx = 0;
    }
}

void draw_rect(int x, int y, int w, int h) {
    if(x < 0 || y < 0 || w < 1 || h < 1) return; // control input
    if(x + w > DISPLAY_WIDTH || y + h > DISPLAY_HEIGHT) return; // control input
    int i, j;
    for(i = 0; i < w; i++)
        for(j = 0; j < h; j++)
            pixels[j + y][i + x] ^= 1;
}

void draw_image(int x, int y, int w, int h, uint8_t *image) {
    int i, j;
    if(x < 0 || y < 0 || w < 0 || h < 0) return;
    if(x + w > DISPLAY_WIDTH || y + h > DISPLAY_HEIGHT) return;
    for(j = 0; j < h; j++)
        for(i = 0; i < w; i++)
            pixels[j + y][i + x] ^= image[j * w + i];

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