#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

uint8_t pixels[32][128];

int main(void) {
    setup_ports();
    setup_display();
    

    game_init();
	while(1) {
        game_update();
        update_display();
    }
	return 0;
}
