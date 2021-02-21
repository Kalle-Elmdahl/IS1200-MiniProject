#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

void check_game_buttons(int btns);
void check_for_start(int sws, int btns);

void check_user_inputs() {
    int sws = (PORTD >> 8) & 0xF; // Switch infromation from port D
    int btns = (PORTD >> 4) & 0xE | (PORTF >> 1) & 0x1; // Button infromation from port D (btn 2-4) and F (btn 1)
    // player2
    btns |= (PORTD << 4) & 0xf0; // Player 2 buttons are located at Port D (chipkit pin 3, 5, 6 & 9) 0->3


    switch(app_state) {
        case START_PAGE:
            check_for_start(sws, btns);
            return;
        case MENU:
            check_menu_buttons(btns);
            break;
        case GAME:
            check_game_buttons(btns);
            break;
    }

    if(sws & 0b1) {
        if(app_state == MENU && game_state == GAME_OVER) game_init(); // Conditions for starting the game
        app_state = GAME;
    } else {
        app_state = MENU;
    }
}


void check_game_buttons(int btns) {

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

    if (game_mode != TWO_PLAYER)
        return;

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

}

void check_menu_buttons(int btns) {

    if (btns & 0x1) menu_select ++;  // right button
    if (btns & 0x8) menu_select --;  // left button

}



void check_for_start(int sws, int btns) {
    // The applications should start if all switches are down and any button is pressed
    if(!sws && btns > 0) {
        app_state = MENU;
        game_state = GAME_OVER;
        menu_select = SELECT_ONE_PLAYER; // Set menu to 1 player default
    }
}