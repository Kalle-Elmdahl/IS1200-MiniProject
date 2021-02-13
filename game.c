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
    
    snakex = (snakex + dxsnake) % 128;
    snakey = (snakey + dysnake) % 32;

    pixels[snakey][snakex] = 1;
}