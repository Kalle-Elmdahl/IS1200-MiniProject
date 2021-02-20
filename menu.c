#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

 
void draw_menu() {

    /* Game menu */
    if (menu_select == 0 && game_mode == ONE_PLAYER)
        draw_text(5, 1, "Resume 1 Player game");
    else if (menu_select == 0 && game_mode == NO_GAME)
        draw_text(5, 1, "Start 1 Player game");
    else if (menu_select == 1)
        draw_text(5, 1, "2 Player");

    /* Sidebar */
    draw_rect(DISPLAY_WIDTH - 1 - 23, 0, 23, DISPLAY_HEIGHT);
    draw_image(DISPLAY_WIDTH - 1 - 16, 1, 9, 16, &lever_up[0][0]);
    draw_text(DISPLAY_WIDTH - 22, 3, "Play!");

    /* Bottom bar */
    draw_rect(0, DISPLAY_HEIGHT - 9, DISPLAY_WIDTH - 24, 9);
    draw_text(5, 3, "<- | -> | Select");
    
}
