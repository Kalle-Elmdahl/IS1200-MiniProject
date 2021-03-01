#include <stdint.h>
#include <stdbool.h>
#include <pic32mx.h>
#include "mipslab.h"  /* Declarations for game */

#define WRITE 0xA0 // Tell the i2c to initiate a write operation
#define READ 0xA1 // Tell the i2c to initiate a read operation

void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

/* Wait for I2C bus to become idle */
void i2c_idle() {
	while(I2C1CON & 0x1F || I2C1STAT & (1 << 14)); //TRSTAT
}

/* Send one byte on I2C bus, return ack/nack status of transaction */
bool i2c_send(uint8_t data) {
	i2c_idle();
	I2C1TRN = data;
	i2c_idle();
	return !(I2C1STAT & (1 << 15)); //ACKSTAT
}

/* Receive one byte from I2C bus */
uint8_t i2c_recv() {
	i2c_idle();
	I2C1CONSET = 1 << 3; //RCEN = 1
	i2c_idle();
	I2C1STATCLR = 1 << 6; //I2COV = 0
	return I2C1RCV;
}

/* Send acknowledge conditon on the bus */
void i2c_ack() {
	i2c_idle();
	I2C1CONCLR = 1 << 5; //ACKDT = 0
	I2C1CONSET = 1 << 4; //ACKEN = 1
}

/* Send not-acknowledge conditon on the bus */
void i2c_nack() {
	i2c_idle();
	I2C1CONSET = 1 << 5; //ACKDT = 1
	I2C1CONSET = 1 << 4; //ACKEN = 1
}

/* Send start conditon on the bus */
void i2c_start() {
	i2c_idle();
	I2C1CONSET = 1 << 0; //SEN
	i2c_idle();
}

/* Send restart conditon on the bus */
void i2c_restart() {
	i2c_idle();
	I2C1CONSET = 1 << 1; //RSEN
	i2c_idle();
}

/* Send stop conditon on the bus */
void i2c_stop() {
	i2c_idle();
	I2C1CONSET = 1 << 2; //PEN
	i2c_idle();
}

/*

function to write_to_memory
accepts: 
- char pointer write_data (With contents to write)
- int memory_address (location to write to)
- int len (amount of bytes to write)

The contents (to the amount of len) of char pointer
write data is stored at the desired memory location.

*/

void write_to_memory(char* write_data, int memory_address, int len) {

    int i;

    // Add memory to be written to variable to write into memory
	// Possibly redundant

	/*
    for (i = 0; i < len; i ++)
        memory_write_data[i] = write_data[i];
	*/

    do {
        i2c_start();
    } while (!i2c_send(WRITE));

    i2c_send(memory_address >> 8); // MSB
    i2c_send(memory_address & 0xFF); // LSB

	for (i = 0; i < len; i ++)
		i2c_send(write_data[i]);

    i2c_stop();

	// Possibly redundant
	/*
    clear_memory_data();
	*/

}


/*

function to read_from_memory
accepts: 
- int memory_address (location to read from)
- int len (amount of bytes to read)

Output is stored in global char pointer:
memory_read_data*

*/

void read_from_memory(int memory_address, int len) {

    int i; 
	uint8_t receive_buffer = I2C1RCV; // Empty recieve buffer

    do {
		i2c_start();
	} while(!i2c_send(WRITE));
	
    i2c_send(memory_address >> 8); // MSB
    i2c_send(memory_address & 0xFF); // LSB
		
	/* Now send another start condition and address of the memory to be read with
	read mode (lowest bit = 1) until the i2c sends acknowledge condition */
	
    do {
		i2c_start();
	} while(!i2c_send(READ));

    for (i = 0; i < len; i ++)
    {
        memory_read_data[i] = i2c_recv();
	    i2c_ack();
    }

    // End sequence by nack after last recieve
	receive_buffer = i2c_recv();
    i2c_nack();
    i2c_stop();

}

// Clean up function, not really necessary 
// but tidies up after memory write
void clear_memory_data() {

    int i;
    for (i = 0; i < 12; i ++) {
        memory_read_data[i] = 0;
        memory_write_data[i] = 0;
    }
}


// Function to reset current highscores from meory.
void clear_highscore_memory() {
    int i;
    char empty[3] = {0, 0, 0};
    for (i = 0; i < 3; i ++)
        write_to_memory(empty,(0x1000) * (i+1),4);
}