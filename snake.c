#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <pic32mx.h>
#include "mipslab.h"

#define SNAKE_INITIAL_LENGTH 4 // Defines the inital length of the snake

enum INITIAL_POSITIONS {
    x1 = (1 + SNAKE_SIZE * 5), 
    y1 = (1 + SNAKE_SIZE),
    x2 = (1 + MAX_X - SIDEBAR_WIDTH - SNAKE_SIZE * 5), 
    y2 = (MAX_Y - SNAKE_SIZE * 2)
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
        
    int number_of_obstacles = 0, j, k;

    switch(difficulty) {
        case MEDIUM:
            number_of_obstacles = 2;
            break;
        case HARD:
            number_of_obstacles = 3;
            break;
    }

    for(i = 0; i < number_of_obstacles; i++)
        for(j = 0; j < 3; j++)
            for(k = 0; k < 3; k++)
                if(obstacle_hit_boxes[current_obstacles[i].type][j][k])
                    if(snake.x[0] == current_obstacles[i].x + k * 3 && snake.y[0] == current_obstacles[i].y + j * 3)
                        return 0;

    return 1;
}