/************************************************************

         Very Advanced Snake on Very Small Display

A game by Kalle Elmdahl and Erik Malm, developed in the KTH 
course IS1200 during spring 2021.

~~~~~~~~~~~~~~~~~~~~~~~~~~ apple.c ~~~~~~~~~~~~~~~~~~~~~~~~~~

Erik and Kalle collaborated on the design of the apple logic.
Code edit has been done by both authors.

************************************************************/

#include <stdint.h>
#include <pic32mx.h>
#include "snake.h"

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
        if(game_mode == TWO_PLAYER && valid_pos) {
            for(i = 0; i < player2.length; i++) {
                if(player2.x[i] == apple.x && player2.y[i] == apple.y) {
                    valid_pos = 0;
                    break;
                }
            }
        }

        int number_of_obstacles = 0;
        switch(difficulty) {
            case MEDIUM:
                number_of_obstacles = 2;
                break;
            case HARD:
                number_of_obstacles = 3;
                break;
        }

        for(i = 0; i < number_of_obstacles; i++) {
            if(apple.x >= current_obstacles[i].x && apple.x <= current_obstacles[i].x + 9) {
                if(apple.y >= current_obstacles[i].y && apple.y <= current_obstacles[i].y + 9) {
                    valid_pos = 0;
                    break;
                }
            }
        }
    
    } while(valid_pos == 0);
}

void display_apple() {
    draw_image(apple.x, apple.y, 3, 3, &apple_icon[0][0]);
}

int is_eating(struct Snake snake) {
    if(snake.x[0] == apple.x && snake.y[0] == apple.y) {
        (*E)++;
        new_apple();
        return 1;
    }
    return 0;
}