#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

void new_obstacle() {
    int valid_pos, i;
    do {
        valid_pos = 1;
        obstacle.x = (TMR1 % (DISPLAY_WIDTH - 1 - SIDEBAR_WIDTH) / SNAKE_SIZE) * SNAKE_SIZE + 1; // Magic to align the obstacle
        obstacle.y = (TMR1 % ((DISPLAY_HEIGHT - 2) / SNAKE_SIZE)) * SNAKE_SIZE + 1; // Magic pt 2
        for(i = 0; i < player1.length; i++) {
            if(player1.x[i] == obstacle.x && player1.y[i] == obstacle.y || apple.x == obstacle.x && apple.y == obstacle.y) {
                valid_pos = 0;
                break;
            }
        }
        if(game_mode == TWO_PLAYER && valid_pos) {
            for(i = 0; i < player2.length; i++) {
                if(player2.x[i] == obstacle.x && player2.y[i] == obstacle.y || apple.x == obstacle.x && apple.y == obstacle.y) {
                    valid_pos = 0;
                    break;
                }
            }
        }
    } while(valid_pos == 0);
}

void display_obstacle() {
    draw_image(obstacle.x, obstacle.y, 5, 5, &sq_obstacle[0][0]);
}

int is_colliding(struct Snake snake) {
    if(snake.x[0] == obstacle.x && snake.y[0] == obstacle.y) {
        // Kill snake
    }
    return 0;
}