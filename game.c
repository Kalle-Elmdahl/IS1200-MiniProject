#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

struct Snake player1;
struct Snake player2;
struct Apple apple;

void calculate_next_frame( void );
void draw_game( void );
void display_game_over( void );

void game_init() {
    player1 = initialize_snake(0);

    if (menu_select == ONE_PLAYER)
        game_mode = ONE_PLAYER;

    if (menu_select == SELECT_TWO_PLAYER) {
        player2 = initialize_snake(1);
        game_mode = TWO_PLAYER;
    }

    game_state = IN_GAME;
    new_apple();
}

void game_update() {   
    if(game_state == IN_GAME) calculate_next_frame();
    switch(game_state) {
        case IN_GAME:
            draw_game();
            break;
        case GAME_OVER:
            display_game_over();
            break;
    }     

}

void calculate_next_frame() {
    player1 = update_snake(player1);
    
    if(is_eating(player1))
        player1.should_grow = 1;

    if(game_mode == TWO_PLAYER) {
        player2 = update_snake(player2);
        if(is_eating(player2))
            player2.should_grow = 1;
    }
}

void draw_game() {

    // Sidebar
    draw_rect(DISPLAY_WIDTH - SIDEBAR_WIDTH, 0, SIDEBAR_WIDTH, DISPLAY_HEIGHT);
    draw_image(MAX_X - 17, 1, 9, 16, &lever_down[0][0]);
    draw_text(MAX_X - 20, 3, "Exit");

    // Props
    display_snake(player1);
    if(game_mode == TWO_PLAYER)
        display_snake(player2);
    
    display_apple();


    // Borders
    draw_rect(0, 0, DISPLAY_WIDTH - SIDEBAR_WIDTH, 1);
    draw_rect(0, 1, 1, DISPLAY_HEIGHT - 2);
    draw_rect(0, MAX_Y, DISPLAY_WIDTH - SIDEBAR_WIDTH, 1);

}

void game_over() {
    game_state = GAME_OVER;
}

void display_game_over() {
    draw_text(0, 0, "Game Over!");
    draw_text(0, 1, "Flip switch to reset.");
}