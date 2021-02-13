#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

void check_buttons() {
    int sws = (PORTD >> 8) & 0xF; // Button infromation from port D
    int btn = (PORTD >> 5) & 0x7; // Switch infromation from port D

    // Button 2: 0b??1
    if (btn & 0b001)
        dysnake = -1;

    // Button 3: 0b?1?
    if (btn & 0b010)
        dxsnake = 1;

    // Button 4: 0b1??
    if (btn & 0b100)
        dxsnake = -1;
}