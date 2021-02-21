#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

void get_menu_text();

 
void draw_menu() {
    /* Game menu */
    get_menu_text(); 
    draw_text(5, 1, menu_text);

    /* Sidebar */
    draw_rect(DISPLAY_WIDTH - 1 - 23, 0, 23, DISPLAY_HEIGHT);
    draw_image(DISPLAY_WIDTH - 1 - 16, 1, 9, 16, &lever_up[0][0]);
    draw_text(DISPLAY_WIDTH - 22, 3, "Play!");

    /* Bottom bar */
    draw_rect(0, DISPLAY_HEIGHT - 9, DISPLAY_WIDTH - 24, 9);
    draw_text(5, 3, "<- | -> | Select");
    
}

void get_menu_text() {

    /* Determine menu text */ 
    if (menu_select == SELECT_ONE_PLAYER) {
        if (game_state == IN_GAME && game_mode == ONE_PLAYER) menu_text = "Resume 1 player game";
        else menu_text = "Start 1 player game";
    }

    if (menu_select == SELECT_TWO_PLAYER) {
        if (game_state == IN_GAME && game_mode == TWO_PLAYER) menu_text = "Resume 2 player game";
        else menu_text = "Start 2 player game";
    }

    if (menu_select == SELECT_AI) {
        if (game_state == IN_GAME && game_mode == AI) menu_text = "Resume AI game";
        else menu_text = "Start AI";
    }

    if (menu_select == SELECT_HIGHSCORE)
        menu_text = "Highscore";

    if (menu_select == SELECT_CREDITS)
        menu_text = "Credits";

}