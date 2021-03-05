#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

uint8_t pixels[DISPLAY_HEIGHT][DISPLAY_WIDTH];
int timeoutcount = 0;
int screen_should_update = 1;
int game_update_time = 5;


int main(void) {
    setup_ports();
    setup_display();
    clear_pixels();
    draw_start_page();
    update_display();
    app_state = START_PAGE;

    setup_leds();
    setup_user_inputs();
    setup_clock();
    i2c_init();
	return 0;
}



void update() {	
    // Clock is updated every 1/10 second
    if (IFS(0) & 0x100) {
		IFSCLR(0) = 0x100;
        (*E)++;

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

		if (timeoutcount == game_update_time) {
            clear_pixels();
            game_update();
            update_display();
            timeoutcount = 0;
		}

	}
}
