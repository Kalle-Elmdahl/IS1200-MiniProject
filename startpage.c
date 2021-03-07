/************************************************************

         Very Advanced Snake on Very Small Display

A game by Kalle Elmdahl and Erik Malm, developed in the KTH 
course IS1200 during spring 2021.

~~~~~~~~~~~~~~~~~~~~~~~~ startpage.c ~~~~~~~~~~~~~~~~~~~~~~~~

Kalle is the main author of startpage.c

************************************************************/

#include <stdint.h>
#include <pic32mx.h>
#include "snake.h"

void draw_title_screen();
void new_apples();

#define initial_x 49
#define title_snake_y 12
#define title_snake_size 2
#define initial_length 4 * title_snake_size
#define number_of_snakes 3

struct title_snake {
    uint8_t x;
    uint8_t y;
    int length;
};

struct title_snake title_snakes[number_of_snakes];

uint8_t title_apple_x[number_of_snakes];

enum INITIAL_POSITIONS {
    x1 = (1 + title_snake_size * 5), 
    x2 = (1 + title_snake_size * 10), 
    x3 = (1 + title_snake_size * 15),
};

static const enum INITIAL_POSITIONS INITIAL_X_POSITIONS[] = {x1, x2, x3};


void init_start_page() {

    int i;
    for(i = 0; i < number_of_snakes; i++) {
        title_snakes[i].x = INITIAL_X_POSITIONS[i];
        title_snakes[i].y = title_snake_y + i * (title_snake_size + 1);
        title_snakes[i].length = initial_length;
        title_apple_x[i] = INITIAL_X_POSITIONS[i] + title_snake_size * 5;
    }

    
}

void draw_start_page() {
    switch(start_state) {
        case SWITCH_WARNING:
            draw_text(40, 0, "Make sure all");
            draw_text(30, 1, "switches are down");
            draw_text(33, 2, "to start the game");
            break;
        case TITLE_SCREEN:
            draw_title_screen();
            break;

    }
}

void draw_title_screen() {
    // Borders
    draw_rect(0, 0, DISPLAY_WIDTH, 1);
    draw_rect(0, 1, 1, DISPLAY_HEIGHT - DISPLAY_ROW_HEIGHT - 1);
    draw_rect(MAX_X, 1, 1, DISPLAY_HEIGHT - DISPLAY_ROW_HEIGHT - 1);

    int i, j;
    for(i = 0; i < number_of_snakes; i++) {
        for(j = 0; j < title_snakes[i].length; j++) {
            draw_rect(((title_snakes[i].x + j - 2) % MAX_X) + 1, title_snakes[i].y, 1, title_snake_size);
        }

        draw_rect(title_apple_x[i], title_snakes[i].y, 1, title_snake_size);
    }

    draw_text(30, 0, "Advanced Snake");

    draw_rect(0, DISPLAY_HEIGHT - DISPLAY_ROW_HEIGHT, DISPLAY_WIDTH, DISPLAY_ROW_HEIGHT);
    draw_text(7, 3, "Press any button to start");
}

void update_start_page() {
    int i, j, more_apples = 0;
    for(i = 0; i < number_of_snakes; i++) {
        if(((title_snakes[i].x + title_snakes[i].length - 2) % MAX_X) + 1 == title_apple_x[i]) {
            title_snakes[i].length = title_snakes[i].length + 5;
            more_apples = 1;
        }

        if((TMR1 % ((TMR1 % 20) + 1)) < 8) title_snakes[i].x++;
        if(title_snakes[i].length > 126)
            for(j = 0; j < number_of_snakes; j++)
                title_snakes[j].length = initial_length;
        
        if(title_snakes[i].x > MAX_X) title_snakes[i].x = 1;
    }
    if(more_apples) new_apples();
}

void new_apples() {
    int valid_pos, i, j;
    for(j = 0; j < number_of_snakes; j++) {
        do {
            valid_pos = 1;
            quicksleep(50);
            title_apple_x[j] = (TMR1 % MAX_X) + 1;
            for(i = 0; i < title_snakes[j].length; i++) {
                if(((title_snakes[j].x + i - 2) % MAX_X) + 1 == title_apple_x[j]) {
                    valid_pos = 0;
                    break;
                }
            }
        
        } while(valid_pos == 0);
    }
}