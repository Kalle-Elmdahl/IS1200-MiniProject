#ifndef __I2C_DEFS_H_
#define __I2C_DEFS_H_

/* Definitions for I2C registers */

/*
Copyright (c) 2015, Axel Isaksson

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <pic32mx.h>

#ifndef I2C1CON

/*--------------------------------------
 * I2C Registers.
 */
#define I2C1CON		PIC32_R (0x5000)
#define I2C1CONCLR	PIC32_R (0x5004)
#define I2C1CONSET	PIC32_R (0x5008)
#define I2C1CONINV	PIC32_R (0x500c)
#define I2C1STAT	PIC32_R (0x5010)
#define I2C1STATCLR	PIC32_R (0x5014)
#define I2C1STATSET	PIC32_R (0x5018)
#define I2C1STATINV	PIC32_R (0x501c)
#define I2C1ADD		PIC32_R (0x5020)
#define I2C1ADDCLR	PIC32_R (0x5024)
#define I2C1ADDSET	PIC32_R (0x5028)
#define I2C1ADDINV	PIC32_R (0x502c)
#define I2C1MSK		PIC32_R (0x5030)
#define I2C1MSKCLR	PIC32_R (0x5034)
#define I2C1MSKSET	PIC32_R (0x5038)
#define I2C1MSKINV	PIC32_R (0x503c)
#define I2C1BRG		PIC32_R (0x5040)
#define I2C1BRGCLR	PIC32_R (0x5044)
#define I2C1BRGSET	PIC32_R (0x5048)
#define I2C1BRGINV	PIC32_R (0x504c)
#define I2C1TRN		PIC32_R (0x5050)
#define I2C1TRNCLR	PIC32_R (0x5054)
#define I2C1TRNSET	PIC32_R (0x5058)
#define I2C1TRNINV	PIC32_R (0x505c)
#define I2C1RCV		PIC32_R (0x5060)

#define I2C2CON		PIC32_R (0x5200)
#define I2C2CONCLR	PIC32_R (0x5204)
#define I2C2CONSET	PIC32_R (0x5208)
#define I2C2CONINV	PIC32_R (0x520c)
#define I2C2STAT	PIC32_R (0x5210)
#define I2C2STATCLR	PIC32_R (0x5214)
#define I2C2STATSET	PIC32_R (0x5218)
#define I2C2STATINV	PIC32_R (0x521c)
#define I2C2ADD		PIC32_R (0x5220)
#define I2C2ADDCLR	PIC32_R (0x5224)
#define I2C2ADDSET	PIC32_R (0x5228)
#define I2C2ADDINV	PIC32_R (0x522c)
#define I2C2MSK		PIC32_R (0x5230)
#define I2C2MSKCLR	PIC32_R (0x5234)
#define I2C2MSKSET	PIC32_R (0x5238)
#define I2C2MSKINV	PIC32_R (0x523c)
#define I2C2BRG		PIC32_R (0x5240)
#define I2C2BRGCLR	PIC32_R (0x5244)
#define I2C2BRGSET	PIC32_R (0x5248)
#define I2C2BRGINV	PIC32_R (0x524c)
#define I2C2TRN		PIC32_R (0x5250)
#define I2C2TRNCLR	PIC32_R (0x5254)
#define I2C2TRNSET	PIC32_R (0x5258)
#define I2C2TRNINV	PIC32_R (0x525c)
#define I2C2RCV		PIC32_R (0x5260)

/*
 * I2C Control register
 */
#define PIC32_I2CCON_SEN	0x00000001
#define PIC32_I2CCON_RSEN	0x00000002
#define PIC32_I2CCON_PEN	0x00000004
#define PIC32_I2CCON_RCEN	0x00000008
#define PIC32_I2CCON_ACKEN	0x00000010
#define PIC32_I2CCON_ACKDT	0x00000020
#define PIC32_I2CCON_STREN	0x00000040
#define PIC32_I2CCON_GCEN	0x00000080
#define PIC32_I2CCON_SMEN	0x00000100
#define PIC32_I2CCON_DISSLW	0x00000200
#define PIC32_I2CCON_A10M	0x00000400
#define PIC32_I2CCON_STRICT	0x00000800
#define PIC32_I2CCON_SLCREL	0x00001000
#define PIC32_I2CCON_SIDL	0x00002000
#define PIC32_I2CCON_ON		0x00008000

/*
 * I2C Status register
 */
#define PIC32_I2CSTAT_TBF	0x00000001
#define PIC32_I2CSTAT_RBF	0x00000002
#define PIC32_I2CSTAT_RW	0x00000004
#define PIC32_I2CSTAT_S		0x00000008
#define PIC32_I2CSTAT_P		0x00000010
#define PIC32_I2CSTAT_DA	0x00000020
#define PIC32_I2CSTAT_I2COV	0x00000040
#define PIC32_I2CSTAT_IWCOL	0x00000080
#define PIC32_I2CSTAT_ADD10	0x00000100
#define PIC32_I2CSTAT_GCSTAT	0x00000200
#define PIC32_I2CSTAT_BCL	0x00000400
#define PIC32_I2CSTAT_TRSTAT	0x00004000
#define PIC32_I2CSTAT_ACKSTAT	0x00008000

#endif

#endif

#define EEPROM_WRITE 0xA0 // 1010 000 (0)
#define EEPROM_READ 0xA1  // 1010 000 (1)
#define EEPROM_MEM_ADD 0x00000

#define HIGHSCORE_ENTRIES 10
#define HIGHSCORE_LENGTH 8

void i2c_idle();
int i2c_send(uint8_t data);
uint8_t i2c_recv();
void i2c_ack();
void i2c_nack();
void i2c_start();
void i2c_stop();
void i2c_restart();
