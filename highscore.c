#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for game */
#include "i2c-defs.h" /* Declarations of I2C-specific addresses */

void save_highscore(char *initials, int score) {

    int i, j;
    for (i = 0; i < 3; i ++) {
        if (highscores[i].score < score) {
            for(j = 2; j >= i; j--) {
                highscores[j] = highscores[j - 1];
            }
            highscores[i].score = score;
            highscores[i].first_name = initials[0];
            highscores[i].last_name = initials[1];
            break;
        }
            

    } 

}


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

    
    char data[8];
    data[0] = memory_write_data[0];
    data[1] = memory_write_data[1];
    data[2] = memory_write_data[2];
    data[3] = memory_write_data[3];
    data[4] = memory_write_data[4];
    data[5] = memory_write_data[5];
    data[6] = memory_write_data[6];
    data[7] = memory_write_data[7];
    // char data = memory_write_data;
    short address = memory_address;

    int len = 8;
    do {
        i2c_start();
    } while (!i2c_send(EEPROM_WRITE));

    i2c_send(address >> 8);
    i2c_send(address);

    int i = 0;
    //i2c_send(data[0]);


    while (len >= 0) {
        i2c_send(data[i++]);
        len--;
    }
    i2c_stop();
}

void write_int(short address, int data) {

    do {
        i2c_start();
    } while (!i2c_send(EEPROM_WRITE));

    byte seg[] = {(data & 0xFF), ((data >> 8) & 0xFF), ((data >> 16) & 0xFF),
                  ((data >> 24) & 0xFF)};

    i2c_send(address >> 8);
    i2c_send(address);

    int i;
    for (i = 0; i < sizeof(int); i++)
        i2c_send(seg[i]);

    i2c_stop();
}

int read_int(short address) {
    int recv = 0;

    do {
        i2c_start();
    } while (!i2c_send(EEPROM_WRITE));

    i2c_send(address >> 8);
    i2c_send(address);

    i2c_start();
    i2c_send(EEPROM_READ);

    int i;
    for (i = 0; i < sizeof(int); i++) {
        recv |= i2c_recv();
        i2c_ack();
    }

    i2c_nack();
    i2c_stop();

    return recv;
}

void highscore_read() {
    
    
    /*
    
    int i;
    
    for(i = 1; i < HIGHSCORE_LENGTH + 1; i++) {
        if(i == 3) {
            entry[i] = ' ';
            continue;
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
    entry[4] = 0;

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