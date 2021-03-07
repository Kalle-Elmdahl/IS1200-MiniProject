/************************************************************

         Very Advanced Snake on Very Small Display

A game by Kalle Elmdahl and Erik Malm, developed in the KTH 
course IS1200 during spring 2021.

~~~~~~~~~~~~~~~~~~~~~~~~~~  main.c ~~~~~~~~~~~~~~~~~~~~~~~~~~

main.c calls the functions required to setup the game and the
logic to keep the game running, and what to display on screen.

Erik and Kalle collaborated on the code.
Code edit has been done by both authors.

************************************************************/

#include <stdint.h>
#include <pic32mx.h>
#include "snake.h"

uint8_t pixels[DISPLAY_HEIGHT][DISPLAY_WIDTH];
int timeoutcount = 0;
int screen_should_update = 1;
int game_update_time = 5;


int main(void) {
    setup_ports();
    setup_display();
    setup_user_inputs();
    init_start_page();
    clear_pixels();
    app_state = START_PAGE;
    draw_start_page();
    update_display();

    setup_leds();
    setup_clock();
    i2c_init();
	return 0;
}



void update() {	
    // Clock is updated every 1/10 second
    if (IFS(0) & 0x100) {
		IFSCLR(0) = 0x100;

        screen_should_update = check_user_inputs(); // returns 1 if i.e. button is clicked

        if(app_state == GAME) {
		    timeoutcount++;
        } else if(screen_should_update) {
            clear_pixels();
            switch(app_state) {
                case START_PAGE:
                    draw_start_page();
                    break;
                case MENU:
                    draw_menu();
                    break;
                case SUB_MENU:
                    draw_sub_menu();
                    break;
                case GAME:
                    break;
            }
            update_display();
            return;
        }

        if(app_state == START_PAGE && start_state == TITLE_SCREEN) {
            (*E)++;
            clear_pixels();
            update_start_page();
            draw_start_page();
            update_display();
        }

		if (timeoutcount == game_update_time) {
            clear_pixels();
            game_update();
            update_display();
            timeoutcount = 0;
		}

	}
}
