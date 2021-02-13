#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

uint8_t pixels[DISPLAY_HEIGHT][DISPLAY_WIDTH];
int timeoutcount = 0;


int main(void) {
    setup_ports();
    setup_display();
    clear_pixels();
    update_display();
    game_init();
    app_state = StartPage;

    setup_leds();
    setup_user_inputs();
    setup_clock();
	return 0;
}

void update() {	
    // Clock is updated every 1/10 second
    if (IFS(0) & 0x100) {

		timeoutcount++;
		IFS(0) = 0;
        check_user_inputs();
        (*E)++;

		if (timeoutcount == 10) {
            // update game every second
            
            clear_pixels();
            switch(app_state) {
                case StartPage:
                    draw_start_page();
                    break;
                case Menu:
                    draw_menu();
                    break;
                case Game:
                    game_update();
                    break;
            }
            update_display();
            timeoutcount = 0;
		}

	}
}
