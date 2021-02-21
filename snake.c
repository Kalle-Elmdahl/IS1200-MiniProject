#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <pic32mx.h>
#include "mipslab.h"

#define SNAKE_INITIAL_LENGTH 4 // Defines the inital length of the snake

enum INITIAL_POSITIONS {
    x1 = (1 + SNAKE_SIZE * 10), 
    y1 = (1 + (SNAKE_SIZE * 3)),
    x2 = (1 + MAX_X - SIDEBAR_WIDTH - SNAKE_SIZE * 10), 
    y2 = (1 + (SNAKE_SIZE * 3))
};

static const enum INITIAL_POSITIONS INITIAL_X_POSITIONS[] = {x1, x2};
static const enum INITIAL_POSITIONS INITIAL_Y_POSITIONS[] = {y1, y2};

struct Snake initialize_snake(uint8_t player) {
    struct Snake snake; // Declare Snake
    snake.length = SNAKE_INITIAL_LENGTH;

    if (player == 0) {
        snake.x = player_1x;
        snake.y = player_1y;
    } else {
        snake.x = player_2x;
        snake.y = player_2y;
    }

    int i;
    /* Determine the starting positions and starting direction for the players */

    for (i = 0; i <= SNAKE_INITIAL_LENGTH; i++) {
        snake.x[i] = INITIAL_X_POSITIONS[player] + (player == 0 ?  -i * SNAKE_WIDTH : i * SNAKE_WIDTH);
        snake.y[i] = INITIAL_Y_POSITIONS[player];
    }

    if (player == 0) snake.direction = 'r'; // l = left, u = up, d = down, r = right
    else snake.direction = 'l';
    
    snake.next_direction = snake.direction;

    return snake;
}

void display_snake(struct Snake snake) {
    int i;

    for (i = 0; i < snake.length; i++) {
        draw_rect(snake.x[i], snake.y[i], SNAKE_SIZE, SNAKE_SIZE);
    }
}

struct Snake update_snake(struct Snake snake, struct Snake other_snake) {
    int i;
    if(snake.should_grow == 1) {
        snake.length = snake.length + 1;
        snake.should_grow = 0;
        new_obstacle();
    }

    for (i = snake.length; i > 0; i--) {
        snake.x[i] = snake.x[i - 1];
        snake.y[i] = snake.y[i - 1];
    }

    snake.direction = snake.next_direction;

    // snake head
    switch (snake.direction) {
        case 'r':
            snake.x[0] = snake.x[0] + SNAKE_WIDTH;
            break;
        case 'd':
            snake.y[0] = snake.y[0] + SNAKE_WIDTH;
            break;
        case 'u':
            snake.y[0] = snake.y[0] - SNAKE_WIDTH;
            break;
        case 'l':
            snake.x[0] = snake.x[0] - SNAKE_WIDTH;
            break;
    }

    if(is_valid_snake(snake, other_snake) == 0) game_over();
    
    return snake;
}

int is_valid_snake(struct Snake snake, struct Snake other_snake) {
    if( snake.x[0] < 1 || 
        snake.y[0] < 1 || 
        snake.x[0] + SNAKE_SIZE > DISPLAY_WIDTH - SIDEBAR_WIDTH || 
        snake.y[0] + SNAKE_SIZE > DISPLAY_HEIGHT) return 0; // Snake is outside of world
    int i;
    for(i = 4; i <= snake.length; i++) // first body part able to collide is the forth, (i = 4)
        if(snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i]) return 0; // Snake is colliding with itself

    if(game_mode == TWO_PLAYER || game_mode == AI)
        for(i = 0; i <= other_snake.length; i++)
            if(snake.x[0] == other_snake.x[i] && snake.y[0] == other_snake.y[i]) return 0;

    if (snake.x[0] == obstacle.x && snake.y[0] == obstacle.y) return 0; // Snake is colliding with obstacle

    return 1;
}