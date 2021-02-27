#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for game */
#include "i2c-defs.h" /* Declarations of I2C-specific addresses */

void highscore_read() {

    char name[2];
    name[0] = 'c';
    name[1] = 0;

    char entry[2];
    entry[1] = 0; // NUL char

    uint8_t ack = 0;


    do {
        i2c_start();
        ack = i2c_send(EEPROM_WRITE);
    } while(!ack);

    i2c_send(EEPROM_MEM_ADD >> 2);
    i2c_send(EEPROM_MEM_ADD);
    i2c_send(name[0]);
    i2c_stop();

    


    i2c_start();
    i2c_send(EEPROM_WRITE);
    i2c_send(EEPROM_MEM_ADD >> 2);
    i2c_send(EEPROM_MEM_ADD);
    i2c_restart();
    i2c_send(EEPROM_READ);
    entry[0] = (i2c_recv() + 48);
    /*
    
    int i;
    
    for(i = 1; i < HIGHSCORE_LENGTH + 1; i++) {
        if(i == 3) {
            entry[i] = ' ';
            continue;
    }

    i2c_ack();
        entry[i] = i2c_recv();
    }
    */
    i2c_stop();
    draw_text(10,0,entry);
}