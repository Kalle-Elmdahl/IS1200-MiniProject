#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

void draw_menu() {
    /* Sidebar */
    draw_rect(DISPLAY_WIDTH - 1 - 20, 0, 20, DISPLAY_HEIGHT);
    draw_image(DISPLAY_WIDTH - 1 - 14, 1, 8, 16, &lever_up[0][0]);
    draw_text(DISPLAY_WIDTH - 20, 3, "Play!");

    /* Bottom bar */
    draw_rect(0, DISPLAY_HEIGHT - 1 - 9, DISPLAY_WIDTH - 22, 9);
    draw_text(5, 3, "<- | -> | Select");
}