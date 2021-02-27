#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for game */
#include "i2c-defs.h" /* Declarations of I2C-specific addresses */


/*
void write_to_memory() {
    uint8_t name[8];
    int i;
    for (i = 0; i < 8; i++) {
        name[i] = 65 + i;
    }
    uint8_t ack = 0;

    do {
        i2c_start();
        ack = i2c_send(EEPROM_WRITE);
    } while(!ack);


    // i2c_start();
    // i2c_send(EEPROM_WRITE);
    i2c_send(EEPROM_MEM_ADD >> 2);
    i2c_send(EEPROM_MEM_ADD);
    i2c_send(EEPROM_WRITE);
    for (i = 0; i < 8; i ++)
        i2c_send(name[i]);
    i2c_stop();
}
*/

void write_to_memory() {

    // char *ok = memory_write_data;

    char ok[5];
    ok[0] = memory_write_data[0];
    ok[1] = memory_write_data[1];
    ok[2] = memory_write_data[2];
    ok[3] = memory_write_data[3];
    ok[4] = 0;

    short address = memory_address;
    int len = 4;
    do {
        i2c_start();
    } while (!i2c_send(EEPROM_WRITE));

    i2c_send(address >> 8);
    i2c_send(address);

    int i = 0;

    while (len >= 0) {
        i2c_send(ok[i++]);
        len--;
    }

    i2c_stop();
}



void highscore_read() {



    /*

    // char name[2];
    // name[0] = 'B';
    // name[1] = 0; // null char
    char entry[HIGHSCORE_LENGTH + 2];
    entry[HIGHSCORE_LENGTH + 1] = 0; // NUL char

    /*uint8_t ack = 0;


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
    
    


    i2c_start();
    i2c_send(EEPROM_WRITE);
    i2c_send(EEPROM_MEM_ADD >> 2);
    i2c_send(EEPROM_MEM_ADD);
    i2c_restart();
    i2c_send(EEPROM_READ);
    entry[0] = (i2c_recv() + 48);
    int i;
    for(i = 1; i < HIGHSCORE_LENGTH + 1; i++) {
        i2c_ack();
        entry[i] = (i2c_recv() + 48);
    }
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

    char entry[5];
    short address = 0x0001000;
    int len = 4;

    do {
        i2c_start();
    } while (!i2c_send(EEPROM_WRITE));

    i2c_send(address >> 8);
    i2c_send(address);

    i2c_start();
    i2c_send(EEPROM_READ);

    int i = 0;

    while (len >= 0) {
        entry[i++] = i2c_recv() + 33;
        i2c_ack();
        len--;
    }

    i2c_nack();
    
    i2c_stop();
    draw_text(10,0,entry);
    // draw_text(10,1,name);
}

void memory_write(char *data, short address) {

    do {
        i2c_start();
    } while (!i2c_send(EEPROM_WRITE));

    i2c_send(address >> 8);
    i2c_send(address);

    int i = 0;

    while (i < 8) {
        i2c_send(data[i++]);
        i++;
    }
    i2c_stop();
}


char memory_read(short address, int len) { // send address: (0x1 << 12) 

    char char_at_memory;

    do {
        i2c_start();
    } while (!i2c_send(EEPROM_WRITE));

    i2c_send(address >> 8);
    i2c_send(address);

    i2c_start();
    i2c_send(EEPROM_READ);

    int i = 0;

    while (i < len) {
        i2c_ack();
        len++;
    }

    char_at_memory = i2c_recv() + 33;

    i2c_nack();
    i2c_stop();

    return char_at_memory;
} 