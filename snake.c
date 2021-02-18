#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <pic32mx.h>
#include "mipslab.h"

#define SNAKE_INITIAL_LENGTH 4 // Defines the inital length of the snake

#define INITIAL_X 1 + (SNAKE_SIZE * 10) // Defines the starting x-coordinate
#define INITIAL_Y 1 + (SNAKE_SIZE * 3) // Defines the starting y-coordinate

struct Snake initialize_snake() {
    struct Snake snake; // Declare Snake of Player 1
    snake.direction = 0b1; // Bits <3:0>: Left, Up, Down, Right
    snake.next_direction = snake.direction;
    snake.length = SNAKE_INITIAL_LENGTH;
    snake.x = player_1x;
    snake.y = player_1y;
    int i;

    for (i = 0; i < SNAKE_INITIAL_LENGTH; i++) {
        snake.x[i] = INITIAL_X - i * SNAKE_WIDTH;
        snake.y[i] = INITIAL_Y;
    }


    return snake;
}

void display_snake(struct Snake snake) {
    int i;

    for (i = 0; i < snake.length; i++) {
        draw_rect(snake.x[i], snake.y[i], SNAKE_WIDTH, SNAKE_WIDTH);
    }
}

struct Snake update_snake(struct Snake snake) {
    int i;
    if(snake.should_grow == 1) {
        snake.length = snake.length + 1;
        snake.should_grow = 0;
    }

    for (i = snake.length - 1; i > 0; i--) {
        snake.x[i] = snake.x[i - 1];
        snake.y[i] = snake.y[i - 1];
    }

    snake.direction = snake.next_direction;

    // snake head
    switch (snake.direction) {
        case 0b1:
            snake.x[0] = snake.x[0] + SNAKE_WIDTH;
            break;
        case 0b10:
            snake.y[0] = snake.y[0] + SNAKE_WIDTH;
            break;
        case 0b100:
            snake.y[0] = snake.y[0] - SNAKE_WIDTH;
            break;
        case 0b1000:
            snake.x[0] = snake.x[0] - SNAKE_WIDTH;
            break;
    }

    if(is_valid_snake(snake) == 0) game_over();
    
    return snake;
}

int is_valid_snake(struct Snake snake) {
    if( snake.x[0] < 1 || 
        snake.y[0] < 1 || 
        snake.x[0] + SNAKE_SIZE > DISPLAY_WIDTH - SIDEBAR_WIDTH || 
        snake.y[0] + SNAKE_SIZE > DISPLAY_HEIGHT) return 0; // Snake is outside of world
    int i;
    for(i = 4; i < snake.length; i++) // first body part able to collide is the forth, (i = 4)
        if(snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i]) return 0; // Snake is colliding with itself
    return 1;
}