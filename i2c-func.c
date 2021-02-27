/* Code by Axel Isaksson 2015 */
#include <pic32mx.h>
#include <stdint.h>
#include "i2c-defs.h"

/* Wait for I2C bus to become idle
 * Author: h4xxel
*/
void i2c_idle() {
    while (I2C1CON & 0x1F || I2C1STAT & (1 << 14))
        ;  // TRSTAT
}

/* Send one byte on I2C bus, return ack/nack status of transaction
 * Author: h4xxel
 */
int i2c_send(byte data) {
    i2c_idle();
    I2C1TRN = data & 0xFF;
    i2c_idle();
    return !(I2C1STAT & (1 << 15));  // ACKSTAT
}

/* Receive one byte from I2C bus
 * Author: h4xxel
 */
byte i2c_recv() {
    i2c_idle();
    I2C1CONSET = 1 << 3;  // RCEN = 1
    i2c_idle();
    I2C1STATCLR = 1 << 6;  // I2COV = 0
    return I2C1RCV;
}

/* Send acknowledge conditon on the bus 
 * Author: h4xxel 
 */
void i2c_ack() {
    i2c_idle();
    I2C1CONCLR = 1 << 5;  // ACKDT = 0
    I2C1CONSET = 1 << 4;  // ACKEN = 1
}

/* Send not-acknowledge conditon on the bus 
 * Author: h4xxel 
 */
void i2c_nack() {
    i2c_idle();
    I2C1CONSET = 1 << 5;  // ACKDT = 1
    I2C1CONSET = 1 << 4;  // ACKEN = 1
}

/* Send start conditon on the bus 
 * Author: h4xxel 
 */
void i2c_start() {
    i2c_idle();
    I2C1CONSET = 1;  // SEN
    i2c_idle();
}

/* Send restart conditon on the bus 
 * Author: h4xxel 
 */
void i2c_restart() {
    i2c_idle();
    I2C1CONSET = 1 << 1;  // RSEN
    i2c_idle();
}

/* Send stop conditon on the bus 
 * Author: h4xxel  
 */
void i2c_stop() {
    i2c_idle();
    I2C1CONSET = 1 << 2;  // PEN
    i2c_idle();
}