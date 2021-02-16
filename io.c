#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

void check_game_buttons(int btns);
void check_for_start(int sws, int btns);

void check_user_inputs() {
    int sws = (PORTD >> 8) & 0xF; // Switch infromation from port D
    int btns = (PORTD >> 4) & 0xE | (PORTF >> 1) & 0x1; // Button infromation from port D (btn 2-4) and F (btn 1)

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
    // Button 1
    if (btns & 0x1)
        dysnake = -1;

    // Button 2
    if (btns & 0x2)
        dxsnake = 1;

    // Button 3
    if (btns & 0x4)
        dxsnake = -1;

    // Button 4
    if (btns & 0x8)
        dysnake = 1;
}

void check_for_start(int sws, int btns) {
    // The applications should start if all switches are down and any button is pressed
    if(!sws && btns > 0) app_state = Menu;
}

int getbtn(int btn) {
    int value = 0;
    switch (btn) {
        case 1:
            value = (PORTF)&2;
            break;
        case 2:
            value = ((PORTD>>5)&7) & 1;
            break;
        case 3:
            value = ((PORTD>>5)&7) & 2;
            break;
        case 4:
            value = ((PORTD>>5)&7) & 4;
            break;
        default:
            value = 0;
    }
    return value;
}