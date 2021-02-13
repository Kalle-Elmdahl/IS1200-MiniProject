#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

void draw_start_page() {
    draw_text(0, 0, "Advanced Snake");
    draw_text(0, 1, "Make sure all switches are down");
    draw_text(0, 3, "Press any button to start");
}