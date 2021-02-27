#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int check_for_start();
void check_menu_buttons();
void check_game_buttons();
void check_sub_menu_buttons();
int last_btns = 0, btns = 0, sws = 0, clicks = 0, updated = 0;

int check_user_inputs() {
    sws = (PORTD >> 8) & 0xF; // Switch infromation from port D
    btns = (PORTD >> 4) & 0xE | (PORTF >> 1) & 0x1; // Button infromation from port D (btn 2-4) and F (btn 1)
    // player2
    btns |= (PORTD << 4) & 0xf0; // Player 2 buttons are located at Port D (chipkit pin 3, 5, 6 & 9) 0->3
    clicks = btns & ~last_btns;


    switch(app_state) {
        case START_PAGE:
            return check_for_start();
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

    if(app_state != GAME && clicks) updated = 1;

    if(sws & 0b1) {
        if(app_state != GAME && game_state == GAME_OVER) game_init(); // Conditions for starting the game
        app_state = GAME;
    } else if(!(sws & 0b1) && app_state == GAME) {
        app_state = MENU;
        updated = 1;
    }
    last_btns = btns;
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

            if (game_mode == AI)
                player2.next_direction = get_AI_direction();

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
            if(initials[selected_initial] != 65 != 1 && clicks & 0x1) 
                initials[selected_initial]--;
            if(initials[selected_initial] != 90 && clicks & 0x2) 
                initials[selected_initial]++;
            if(selected_initial != 1 && clicks & 0x4) 
                selected_initial++;
            if(selected_initial != 0 && clicks & 0x8) 
                selected_initial--;
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


int check_for_start() {
    // The applications should start if all switches are down and any button is pressed
    if(sws || btns == 0) return 0;
    
    app_state = MENU;
    game_state = GAME_OVER;
    game_mode = ONE_PLAYER; // Set game mode to 1 player default
    game_speed = NORMAL;

    char data[5];
    data[0] = 'A';
    data[1] = 'B';
    data[2] = 'C';
    data[3] = 'D';
    data[4] = 0;

    write_to_memory(data);

    /*
    int i;

    char data[9];
    data[0] = 'E';
    data[1] = 'F';
    data[2] = 'G';
    data[3] = 'H';
    data[4] = 'I';
    data[5] = 'J';
    data[6] = 'K';
    data[7] = 'L';
    data[8] = 0;

    memory_write(data,0x1000);
    */


    return 1;
}