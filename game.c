#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int snakex = 0;
int snakey = 0;

void game_init() {
    int i, j;
}

void game_update() {
    int i, j;
    for(i = 0; i < 32; i++)
        for(j = 0; j < 128; j++)
                pixels[i][j] = 0;

    pixels[snakey][snakex] = 1;

    snakex = (snakex + 1) % 128;
    snakey = (snakey + 1) % 32;
}