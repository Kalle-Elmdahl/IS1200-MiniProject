#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int snakex = 0;
int snakey = 0;

void game_init() {
    int i, j;
    dxsnake = 1;
    dysnake = 1;
}

void game_update() {        
    draw_rect(DISPLAY_WIDTH - 1 - 20, 0, 20, DISPLAY_HEIGHT);
    draw_image(DISPLAY_WIDTH - 1 - 14, 1, 8, 16, &lever_down[0][0]);
    draw_text(DISPLAY_WIDTH - 19, 3, "Exit");
    
    snakex = (snakex + dxsnake) % 128;
    snakey = (snakey + dysnake) % 32;

    pixels[snakey][snakex] = 1;
}