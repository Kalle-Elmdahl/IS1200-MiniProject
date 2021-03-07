/************************************************************

         Very Advanced Snake on Very Small Display

A game by Kalle Elmdahl and Erik Malm, developed in the KTH 
course IS1200 during spring 2021.

~~~~~~~~~~~~~~~~~~~~~~~~ obstacles.c ~~~~~~~~~~~~~~~~~~~~~~~~

Erik is the original author of obstacles.c

Erik and Kalle collaborated on the project and have both contributed 
to the code in menu.c. Code edits have been done by Kalle.

************************************************************/

#include <stdint.h>
#include <pic32mx.h>
#include "snake.h"

void generate_obstacle(int save_index);


void initialize_obstacles() {
    int number_of_obstacles = 0, i, j;
    switch(difficulty) {
        case MEDIUM:
            number_of_obstacles = 2;
            break;
        case HARD:
            number_of_obstacles = 3;
            break;
        default:
            break;
    }

    for(i = 0; i < number_of_obstacles; i++) {
        generate_obstacle(i);
        for(j = 0; j < TMR1 % 200; j++); // little delay to make sure obsticles are actually randomly generated
    }

}

#define obstacle_left_bound 1 + (SNAKE_SIZE * 6) // make sure obsticle spawns at least 6 snake bits from left side
#define obstacle_right_bound DISPLAY_WIDTH - SIDEBAR_WIDTH - (6 * SNAKE_SIZE) - 9 // 9 is size of one obstacle
#define obstacle_top_bound 1 + SNAKE_SIZE
#define obstacle_bottom_bound DISPLAY_HEIGHT - 1 - 9 - SNAKE_SIZE

const int obstacle_area_width = (obstacle_right_bound + (obstacle_left_bound * -1)) / SNAKE_SIZE;
const int obstacle_area_height = (obstacle_bottom_bound + (obstacle_top_bound * -1)) / SNAKE_SIZE;

void generate_obstacle(int save_index) {
    int valid_pos, i;    
    do {
        valid_pos = 1;
        current_obstacles[save_index].x = (TMR1 % obstacle_area_width) * SNAKE_SIZE + obstacle_left_bound;
        current_obstacles[save_index].y = (TMR1 % obstacle_area_height) * SNAKE_SIZE + obstacle_top_bound;

        // check if obstacle is overlapping with other obstacle
        for(i = 0; i < save_index; i++) {
            if(current_obstacles[i].x - 9 <= current_obstacles[save_index].x && current_obstacles[i].x + 9 >= current_obstacles[save_index].x) {
                // x is within bounds
                if(current_obstacles[i].y - 9 <= current_obstacles[save_index].y && current_obstacles[i].y + 9 >= current_obstacles[save_index].y) {
                    valid_pos = 0;
                    break;
                }
            }
        }
    } while(valid_pos == 0);
    current_obstacles[save_index].type = TMR1 % 3;
}

void display_obstacles() {
    int number_of_obstacles, i;
    switch(difficulty) {
        case MEDIUM:
            number_of_obstacles = 2;
            break;
        case HARD:
            number_of_obstacles = 3;
            break;
        default:
            break;
    }
    for(i = 0; i < number_of_obstacles; i++) {
        draw_image(current_obstacles[i].x, current_obstacles[i].y, 9, 9, &obstacles[current_obstacles[i].type][0][0]);
    }
}