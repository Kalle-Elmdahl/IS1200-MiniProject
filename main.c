#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include "i2c-defs.h" /* Declarations of I2C-specific addresses */

uint8_t pixels[DISPLAY_HEIGHT][DISPLAY_WIDTH];
int timeoutcount = 0;
int screen_should_update = 1;
game_update_time = 5;


int main(void) {
    setup_ports();
    setup_display();
    clear_pixels();
    draw_start_page();
    update_display();
    write_to_memory();
    app_state = START_PAGE;

    setup_leds();
    setup_user_inputs();
    setup_clock();
	return 0;
}

void write_to_memory() {
    char name[2];
    name[0] = 'B';
    name[1] = 0; // null char
    uint8_t ack = 0;

    do {
        i2c_start();
        ack = i2c_send(EEPROM_WRITE);
    } while(!ack);

    // i2c_start();
    // i2c_send(EEPROM_WRITE);
    i2c_send(EEPROM_MEM_ADD >> 2);
    i2c_send(EEPROM_MEM_ADD);
    i2c_send(name[0]);
    i2c_stop();
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
