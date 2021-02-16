#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

#define SNAKE_WIDTH 3 // Defines the width of the snake
#define SNAKE_INITIAL_LENGTH 4 // Defines the inital length of the snake

#define INITIAL_X 41 // Defines the starting x-coordinate
#define INITIAL_Y 11 // Defines the starting y-coordinate

struct Snake initialize_snake() {
    struct Snake snake; // Declare Snake of Player 1
    snake.direction = 0b1; // Bits <3:0>: Left, Up, Down, Right
    snake.next_direction = snake.direction;
    snake.length = SNAKE_INITIAL_LENGTH;
    int i;
    
    // Snake_Body * tempbody = (struct Snake_Body*) malloc(sizeof(struct Snake_Body) * 126);
    // snake.body = (struct Snake_Body *) malloc(sizeof(struct Snake_Body) * 126);

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
    
    return snake;
}