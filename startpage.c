#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

void draw_title_screen();

#define initial_x 50
#define initial_y 20
#define initial_length 10

uint8_t title_snake_x[50];
uint8_t title_snake_y[50];
struct Snake title_snake;

void init_start_page() {
    title_snake.x = title_snake_x;
    title_snake.y = title_snake_y;
    title_snake.length = initial_length;

    int i;
    for(i = 0; i <= initial_length; i++) {
        title_snake.x[i] = (initial_x - i * SNAKE_SIZE);
        title_snake.y[i] = initial_y;
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

    display_snake(title_snake);

    draw_text(30, 0, "Advanced Snake");

    draw_rect(0, DISPLAY_HEIGHT - DISPLAY_ROW_HEIGHT, DISPLAY_WIDTH, DISPLAY_ROW_HEIGHT);
    draw_text(7, 3, "Press any button to start");
}