#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

void check_game_buttons(int btns);
void check_for_start(int sws, int btns);

void check_user_inputs() {
    int sws = (PORTD >> 8) & 0xF; // Button infromation from port D
    int btns = (PORTD >> 5) & 0x7; // Switch infromation from port D

    switch(app_state) {
        case StartPage:
            check_for_start(sws, btns);
            return;
        case Menu:
            break;
        case Game:
            check_game_buttons(btns);
            break;
    }

    if(sws & 0b1) {
        app_state = Game;
    } else {
        app_state = Menu;
    }
}

void check_game_buttons(int btns) {
    // Button 2: 0b??1
    if (btns & 0b001)
        dysnake = -1;

    // Button 3: 0b?1?
    if (btns & 0b010)
        dxsnake = 1;

    // Button 4: 0b1??
    if (btns & 0b100)
        dxsnake = -1;
}

void check_for_start(int sws, int btns) {
    // The applications should start if all switches are down and any button is pressed
    if(!sws && btns > 0) app_state = Game;
}