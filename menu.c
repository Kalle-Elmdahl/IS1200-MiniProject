#include <stdint.h>
#include <pic32mx.h>
#include "snake.h"

void get_menu_text();
const struct menu_item menu_items[number_of_menu_items];
int current_menu_position = 0;

 
void draw_menu() {
    /* Game menu */
    int text_position_x = (DISPLAY_WIDTH - SIDEBAR_WIDTH) / 2 - menu_items[current_menu_position].text_width / 2;

    if(current_menu_position != 0) draw_image(text_position_x - 3 - 3, 10, 3, 5, &arrow_left[0][0]);

    
    draw_text(text_position_x, 1, menu_items[current_menu_position].text); 

    if(current_menu_position != number_of_menu_items - 1)
        draw_image(menu_items[current_menu_position].text_width + text_position_x + 3, 10, 3, 5, &arrow_right[0][0]); 
    


    /* Sidebar */
    draw_rect(DISPLAY_WIDTH - SIDEBAR_WIDTH, 0, SIDEBAR_WIDTH, DISPLAY_HEIGHT);
    draw_image(MAX_X - 17, 1, 9, 16, &lever_up[0][0]);
    draw_text(DISPLAY_WIDTH - 22, 3, "Play!");

    /* Bottom bar */
    draw_rect(0, DISPLAY_HEIGHT - 8, DISPLAY_WIDTH - SIDEBAR_WIDTH, 8);
    draw_image(3, DISPLAY_HEIGHT - 6, 3, 5, &arrow_left[0][0]);
    draw_image(10, DISPLAY_HEIGHT - 6, 3, 5, &arrow_right[0][0]);
    draw_text(15, 3, "Select");
    
}

void select_current_menu_item() {
    if(menu_items[current_menu_position].sub_menu != -1) {
        current_sub_menu = menu_items[current_menu_position].sub_menu;
        app_state = SUB_MENU;
        init_sub_menu();
        return;
    }

    // No sub-menu
    switch(menu_items[current_menu_position].action) {
        case 0:
            game_over(); // Restart game
            break;
    }
}

// char *text;
// int text_width;
// int sub_menu;
// int action;
const struct menu_item menu_items[number_of_menu_items] = {
    {
        "Restart game",
        56,
        -1,
        0
    },
    {
        "Game mode",
        44,
        0,
        -1
    },
    {
        "Speed",
        22,
        1,
        -1
    },
    {
        "Difficulty",
        43,
        4,
        -1
    },
    {
        "Credits",
        31,
        2,
        -1
    },
    {
        "Highscore",
        41,
        3,
        -1
    },
};