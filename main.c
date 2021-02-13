#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

uint8_t pixels[32][128];
int timeoutcount = 0;

int main(void) {
    setup_ports();
    setup_display();
    setup_user_inputs();
    

    game_init();
	return 0;
}

void update() {	
    // Clock is updated every 10 ms
    if (IFS(0) & 0x100) {

		timeoutcount++;
		IFS(0) = 0;
        check_buttons();
        (*E)++;

		if (timeoutcount == 10) {
            // update game every second
            game_update();
            update_display();
            timeoutcount = 0;
		}

	}
}
