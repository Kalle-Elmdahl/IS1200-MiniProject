#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"


void new_apple() {
    int valid_pos, i;
    do {
        valid_pos = 1;
        apple.x = (TMR1 % (DISPLAY_WIDTH - 1 - SIDEBAR_WIDTH) / SNAKE_SIZE) * SNAKE_SIZE + 1; // Magic to align the apple
        apple.y = (TMR1 % ((DISPLAY_HEIGHT - 2) / SNAKE_SIZE)) * SNAKE_SIZE + 1; // Magic pt 2
        for(i = 0; i < player1.length; i++) {
            if(player1.x[i] == apple.x && player1.y[i] == apple.y) {
                valid_pos = 0;
                break;
            }
        }
    } while(valid_pos == 0);
}

void display_apple() {
    draw_image(apple.x, apple.y, 3, 3, &apple_icon[0][0]);
}

int is_eating(struct Snake snake) {
    if(snake.x[0] == apple.x && snake.y[0] == apple.y) {
        new_apple();
        return 1;
    }
    return 0;
}