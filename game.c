/************************************************************

         Very Advanced Snake on Very Small Display

A game by Kalle Elmdahl and Erik Malm, developed in the KTH 
course IS1200 during spring 2021.

~~~~~~~~~~~~~~~~~~~~~~~~~~ game.c ~~~~~~~~~~~~~~~~~~~~~~~~~~

Kalle is the architect behind the game logic.

Erik and Kalle collaborated on the project and have both contributed 
to the code in game.c

************************************************************/

#include <stdint.h>
#include <pic32mx.h>
#include <math.h>
#include "snake.h"

struct Snake player1;
struct Snake player2;
struct Apple apple;
struct Obstacle obstacle;

int losing_player;
char score[4];
int score_text_width;
int selected_letter = 0;

void calculate_next_frame( void );
void draw_game( void );
void display_game_over( void );
void display_write_highscore( void );
void game_over( int player );

void game_init() {
    player1 = initialize_snake(0);

    if (game_mode == TWO_PLAYER || game_mode == AI)
        player2 = initialize_snake(1);

    if(game_mode == AI) init_ai();

    game_state = IN_GAME;
    new_apple();
    initialize_obstacles();
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
        case WRITING_HIGHSCORE:
            display_write_highscore();
            break;
    }     
}

void calculate_next_frame() {
    player1 = update_snake(player1);
    int player_one_is_valid, player_two_is_valid;
    
    if(is_eating(player1))
        player1.should_grow = 1;

    if(game_mode == TWO_PLAYER || game_mode == AI) {
        if(game_mode == AI) check_ai_path(player1.should_grow); // if player one is eating the apple, a new path should be generated
        player2 = update_snake(player2);
        if(is_eating(player2))
            player2.should_grow = 1;

        player_two_is_valid = is_valid_snake(player2);
    }

    player_one_is_valid = is_valid_snake(player1);

    if(!player_one_is_valid && !player_two_is_valid) game_over(0);
    else if(!player_one_is_valid) game_over(1);
    else if(!player_two_is_valid) game_over(2);
}

void draw_game() {

    // Sidebar
    draw_rect(DISPLAY_WIDTH - SIDEBAR_WIDTH, 0, SIDEBAR_WIDTH, DISPLAY_HEIGHT);
    draw_image(MAX_X - 17, 1, 9, 16, &lever_down[0][0]);
    draw_text(MAX_X - 20, 3, "Exit");

    // Props
    display_snake(player1);
    if(game_mode == TWO_PLAYER || game_mode == AI)
        display_snake(player2);
    
    display_apple();
    display_obstacles();


    // Borders
    draw_rect(0, 0, DISPLAY_WIDTH - SIDEBAR_WIDTH, 1);
    draw_rect(0, 1, 1, DISPLAY_HEIGHT - 2);
    draw_rect(0, MAX_Y, DISPLAY_WIDTH - SIDEBAR_WIDTH, 1);

}

void game_over(int player) {
    game_state = GAME_OVER;
    losing_player = player;
    int i = 0;
    if(player1.length > 99) score[i++] = player1.length / 100 + 48;
    if(player1.length > 9) score[i++] = (player1.length / 10) % 10 + 48;
    score[i++] = player1.length % 10 + 48;
    score[i++] = 0;
    score_text_width = i * 5;

    // Reset highscore write
    letters[0] = 65;
    letters[1] = 65;
    letters[2] = 65;
    selected_letter = 0;
}

void display_game_over() {
    int text_x;
    draw_rect(DISPLAY_WIDTH - SIDEBAR_WIDTH, 0, SIDEBAR_WIDTH, DISPLAY_HEIGHT);
    draw_image(MAX_X - 17, 1, 9, 16, &lever_down[0][0]);
    draw_text(MAX_X - 22, 3, "Reset");
    draw_text((MAX_X - SIDEBAR_WIDTH) / 2 - 22, 0, "Game Over!");
    switch(game_mode) {
        case ONE_PLAYER:
            text_x = SCREEN_CENTER - 13 - score_text_width / 2;
            draw_text(text_x, 1, "Score");
            draw_text(text_x + 26, 1, score);
            // Bottom bar
            draw_rect(0, DISPLAY_HEIGHT - 8, DISPLAY_WIDTH - SIDEBAR_WIDTH, 8);
            draw_text(3, 3, "Save highscore");
            break;
        case TWO_PLAYER:
            if(losing_player == 0) {
                draw_text(0, 1, "Draw");
            } else if(losing_player == 1) {
                draw_text(0, 1, "Player 2 won");
            } else if(losing_player == 2) {
                draw_text(0, 1, "Player 1 won");
            }
            break;
        case AI:
            if(losing_player == 0) {
                draw_text(0, 1, "Draw");
            } else if(losing_player == 1) {
                draw_text(0, 1, "AI won");
            } else if(losing_player == 2) {
                draw_text(0, 1, "You won");
            }
            break;
    }
}

void display_write_highscore() {
    draw_text(SCREEN_CENTER - 40, 0, "Enter your name");

    draw_text(SCREEN_CENTER - 4, 1, letters);
    draw_image(SCREEN_CENTER - 4 + selected_letter * 4, 16, 5, 3, &arrow_up[0][0]);

    /* Sidebar */
    draw_rect(DISPLAY_WIDTH - SIDEBAR_WIDTH, 0, SIDEBAR_WIDTH, DISPLAY_HEIGHT);
    draw_image(MAX_X - 17, 1, 9, 16, &lever_down[0][0]);
    draw_text(MAX_X - 20, 3, "Save");

    /* Bottom bar */
    draw_rect(0, DISPLAY_HEIGHT - 8, DISPLAY_WIDTH - SIDEBAR_WIDTH, 8);
    draw_image(3, DISPLAY_HEIGHT - 6, 3, 5, &arrow_left[0][0]);
    draw_image(8, DISPLAY_HEIGHT - 6, 3, 5, &arrow_right[0][0]);
    draw_image(13, DISPLAY_HEIGHT - 6, 5, 3, &arrow_up[0][0]);
    draw_image(20, DISPLAY_HEIGHT - 6, 5, 3, &arrow_down[0][0]);
}