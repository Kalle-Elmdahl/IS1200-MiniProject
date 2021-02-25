#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

#define LIST_LEFT_PADDING 18

void draw_game_mode();
void draw_speed();
void update_game_mode(int btns);
void update_speed(int btns);
void draw_credits();
void draw_highscore();
int current_list_item = 0;

void init_sub_menu() {
    current_list_item = 0;
}

void draw_sub_menu() {
    switch(current_sub_menu) {
        case GAME_MODE:
            draw_game_mode();
            break;
        case SPEED:
            draw_speed();
            break;
        case CREDITS:
            draw_credits();
            break;
        case HIGHSCORE:
            draw_highscore();
            break;
        default:
            return;
    }

    /* Sidebar */
    draw_rect(DISPLAY_WIDTH - SIDEBAR_WIDTH, 0, SIDEBAR_WIDTH, DISPLAY_HEIGHT);
    draw_image(MAX_X - 17, 1, 9, 16, &lever_up[0][0]);
    draw_text(DISPLAY_WIDTH - 22, 3, "Play!");

    /* Bottom bar */
    draw_rect(0, DISPLAY_HEIGHT - 8, DISPLAY_WIDTH - SIDEBAR_WIDTH, 8);
    draw_image(3, DISPLAY_HEIGHT - 6, 5, 3, &arrow_up[0][0]);
    draw_image(10, DISPLAY_HEIGHT - 6, 5, 3, &arrow_down[0][0]);
    draw_text(18, 3, "Select");
    draw_text(45, 3, "Back");
}

void update_sub_menu(int btns) {
    switch(current_sub_menu) {
        case GAME_MODE:
            update_game_mode(btns);
            break;
        case SPEED:
            update_speed(btns);
            break;
    }
}

void draw_game_mode() {
    draw_text(LIST_LEFT_PADDING, 0, "1 player");
    draw_text(LIST_LEFT_PADDING, 1, "2 player");
    draw_text(LIST_LEFT_PADDING, 2, "AI");
    draw_image(60, 2 + current_list_item * 8, 3, 5, &arrow_left[0][0]);
    draw_image(5, 2 + game_mode * 8, 6, 5, &check_box[0][0]);
}

void update_game_mode(int btns) {
    if(btns & 0x8 && current_list_item != 0) current_list_item--;
    if(btns & 0x4 && current_list_item != 2) current_list_item++;
    if(btns & 0x2) {
        game_mode = current_list_item;
        game_state = GAME_OVER;
    }
}

void draw_speed() {
    draw_text(LIST_LEFT_PADDING, 0, "Fast");
    draw_text(LIST_LEFT_PADDING, 1, "Normal");
    draw_text(LIST_LEFT_PADDING, 2, "Slow");
    draw_image(50, 2 + current_list_item * 8, 3, 5, &arrow_left[0][0]);
    draw_image(5, 2 + game_speed * 8, 6, 5, &check_box[0][0]);
}

void update_speed(int btns) {
    if(btns & 0x8 && current_list_item != 0) current_list_item--;
    if(btns & 0x4 && current_list_item != 2) current_list_item++;
    if(btns & 0x2) {
        game_speed = current_list_item;
        game_state = GAME_OVER;
        switch(game_speed) {
            case FAST:
                game_update_time = 2;
                break;
            case NORMAL:
                game_update_time = 5;
                break;
            case SLOW:
                game_update_time = 10;
                break;
        }
    }
}

void draw_credits() {
    draw_text(3, 0, "Game made by");
    draw_text(3, 1, "Erik and Kalle");
}

void draw_highscore() {
    highscore_read();
}