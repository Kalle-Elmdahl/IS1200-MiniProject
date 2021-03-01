#include <stdint.h>
#include <stdbool.h>
#include <pic32mx.h>
#include "mipslab.h"  /* Declarations for game */

#define WRITE 0xA0
#define READ 0xA1
#define address 0x1000

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

/* Convert 8.8 bit fixed point to string representation*/
char *fixed_to_string(uint16_t num, char *buf) {
	bool neg = false;
	uint32_t n;
	char *tmp;
	
	if(num & 0x8000) {
		num = ~num + 1;
		neg = true;
	}
	
	buf += 4;
	n = num >> 8;
	tmp = buf;
	do {
		*--tmp = (n  % 10) + '0';
		n /= 10;
	} while(n);
	if(neg)
		*--tmp = '-';
	
	n = num;
	if(!(n & 0xFF)) {
		*buf = 0;
		return tmp;
	}
	*buf++ = '.';
	while((n &= 0xFF)) {
		n *= 10;
		*buf++ = (n >> 8) + '0';
	}
	*buf = 0;
	
	return tmp;
}

void write_to_memory(char* write_data, int memory_address, int len) {

    int i;

    // Add memory to be written to variabel to write into memory
    for (i = 0; i < len; i ++)
        memory_write_data[i] = write_data[i];

    do {
        i2c_start();
    } while (!i2c_send(WRITE));

    i2c_send(memory_address >> 8); // MSB
    i2c_send(memory_address & 0xFF); // LSB

	for (i = 0; i < len; i ++)
		i2c_send(memory_write_data[i]);

    i2c_stop();

    clear_memory_data();

}

void read_from_memory(int memory_address, int len) {

    int i; 
	uint8_t receive_buffer = I2C1RCV;

    do {
		i2c_start();
	} while(!i2c_send(WRITE));
	
    i2c_send(memory_address >> 8);
    i2c_send(memory_address & 0xFF);
		
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

	receive_buffer = i2c_recv();
    i2c_nack();
    
    i2c_stop();

}

void clear_memory_data() {

    int i;

    for (i = 0; i < 12; i ++) {
        memory_read_data[i] = 0;
        memory_write_data[i] = 0;
    }

}


uint32_t strlen(char *str) {
	uint32_t n = 0;
	while(*str++)
		n++;
	return n;
}
