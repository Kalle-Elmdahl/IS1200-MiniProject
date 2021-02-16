#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"


void new_apple() {
    apple.x = 10;
    apple.y = 10;
}

void display_apple() {
    draw_image(apple.x, apple.y, 6, 6, &apple_icon[0][0]);
}