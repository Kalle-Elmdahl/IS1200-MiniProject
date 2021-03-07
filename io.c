#include <stdint.h>
#include <pic32mx.h>
#include "snake.h"

void check_for_start();
void check_menu_buttons();
void check_game_buttons();
void check_sub_menu_buttons();
int last_btns = 0, btns = 0, last_sws = 0xf, sws = 0, switch_updates = 0, clicks = 0, updated = 0;

int check_user_inputs() {
    sws = (PORTD >> 8) & 0xF; // Switch infromation from port D
    btns = (PORTD >> 4) & 0xE | (PORTF >> 1) & 0x1; // Button infromation from port D (btn 2-4) and F (btn 1)
    // player2
    btns |= (PORTD << 4) & 0xf0; // Player 2 buttons are located at Port D (chipkit pin 3, 5, 6 & 9) 0->3
    clicks = btns & ~last_btns;
    switch_updates = sws & ~last_sws | ~sws & last_sws;


    switch(app_state) {
        case START_PAGE:
            check_for_start();
            break;
        case MENU:
            check_menu_buttons();
            break;
        case SUB_MENU:
            check_sub_menu_buttons();
            break;
        case GAME:
            check_game_buttons();
            break;
    }

    if(clicks || switch_updates) updated = 1;

    if(sws & 0b1 && app_state != START_PAGE) {
        if(app_state != GAME && game_state != IN_GAME) game_init(); // Conditions for starting the game
        if(app_state != GAME && game_mode == AI)
            if(btns & 0x8) ai_debug = 1;
            else ai_debug = 0;
        
        app_state = GAME;
    } else if(!(sws & 0b1) && app_state == GAME) {
        if (game_state == WRITING_HIGHSCORE) {
            // Save highscore
            save_highscore(letters, player1.length);
        }
        app_state = MENU;
    }
    last_btns = btns;
    last_sws = sws;
    return updated;
}


void check_game_buttons() {
    switch(game_state) {
        case IN_GAME:
            /* Player 1 buttons */
            // Button 1 -> right
            if (btns & 0x1 && player1.direction != 'l')
                player1.next_direction = 'r';

            // Button 2 -> down
            if (btns & 0x2 && player1.direction != 'u')
                player1.next_direction = 'd';

            // Button 3 -> up
            if (btns & 0x4 && player1.direction != 'd')
                player1.next_direction = 'u';

            // Button 4 -> left
            if ((btns & 0x8) && player1.direction != 'r')
                player1.next_direction = 'l';

            if (game_mode != TWO_PLAYER) return;

            /* Player 2 buttons */
            // Button 1 -> right
            if (btns & 0x10 && player2.direction != 'l')
                player2.next_direction = 'r';

            // Button 2 -> down
            if (btns & 0x20 && player2.direction != 'u')
                player2.next_direction = 'd';

            // Button 3 -> up
            if (btns & 0x40 && player2.direction != 'd')
                player2.next_direction = 'u';

            // Button 4 -> left
            if (btns & 0x80 && player2.direction != 'r')
                player2.next_direction = 'l';
            break;
        case GAME_OVER:
            if(game_mode == ONE_PLAYER && clicks & 0x8) 
                game_state = WRITING_HIGHSCORE;
            break;
        case WRITING_HIGHSCORE:
            if(letters[selected_letter] != 65 && clicks & 0x1) 
                letters[selected_letter]--;
            if(letters[selected_letter] != 90 && clicks & 0x2) 
                letters[selected_letter]++;
            if(selected_letter != 1 && clicks & 0x4) 
                selected_letter++;
            if(selected_letter != 0 && clicks & 0x8) 
                selected_letter--;
            break;
    }

}

void check_menu_buttons() {

    if (clicks & 0x8 && current_menu_position > 0) 
        current_menu_position--;  // left button
    
    if (clicks & 0x4 && current_menu_position < number_of_menu_items - 1) 
        current_menu_position++;  // right button
    
    if (clicks & 0x2) select_current_menu_item();  // Select button

}

void check_sub_menu_buttons() {
    if (clicks & 0x1) {
        app_state = MENU;  // Back button
        return;
    }
    update_sub_menu(clicks);
}


void check_for_start() {
    if(sws) {
        start_state = SWITCH_WARNING;
    } else start_state = TITLE_SCREEN;

    // The applications should start if all switches are down and any button is pressed
    if(start_state == TITLE_SCREEN && btns != 0) {
        app_state = MENU;
        game_state = GAME_OVER;
        game_mode = ONE_PLAYER; // Set game mode to 1 player default
        game_speed = NORMAL;
        difficulty = EASY;
    }
}