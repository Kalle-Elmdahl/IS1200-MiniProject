#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

void check_game_buttons(int btns);
void check_for_start(int sws, int btns);

void check_user_inputs() {
    int sws = (PORTD >> 8) & 0xF; // Switch infromation from port D
    int btns = (PORTD >> 4) & 0xE | (PORTF >> 1) & 0x1; // Button infromation from port D (btn 2-4) and F (btn 1)
    // player2
    int player2btns = (PORTD) & 0xf; // Player 2 buttons are located at Port D 0->3


    switch(app_state) {
        case START_PAGE:
            check_for_start(sws, btns);
            return;
        case MENU:
            break;
        case GAME:
            check_game_buttons(btns);
            break;
    }

    if(sws & 0b1) {
        if(app_state == MENU && game_state == GAME_OVER) game_init();
        app_state = GAME;
    } else {
        app_state = MENU;
    }
}

void check_game_buttons(int btns) {
    // Button 1
    if (btns & 0x1 || btns & 0x20 && player1.direction != 0b1000)
        player1.next_direction = 0b1;

    // Button 2
    if (btns & 0x2 && player1.direction != 0b100)
        player1.next_direction = 0b10;

    // Button 3
    if (btns & 0x4 && player1.direction !=0b10)
        player1.next_direction = 0b100;

    // Button 4
    if ((btns & 0x8) && player1.direction !=0b1)
        player1.next_direction = 0b1000;
}

void check_for_start(int sws, int btns) {
    // The applications should start if all switches are down and any button is pressed
    if(!sws && btns > 0) {
        app_state = MENU;
        game_init();
    }
}