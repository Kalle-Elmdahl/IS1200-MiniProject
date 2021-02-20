#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

void setup_ports( void ) {
    /*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
    SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;
}

void setup_display(void) {
    DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);
	
	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);
	
	spi_send_recv(0x8D);
	spi_send_recv(0x14);
	
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);
	
	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);
	
	spi_send_recv(0xA1);
	spi_send_recv(0xC8);
	
	spi_send_recv(0xDA);
	spi_send_recv(0x20);
	
	spi_send_recv(0xAF);


}

volatile int* E;

void setup_leds() {
    // Register TRISE has address 0xbf886100
    // initialize the port using your own volatile pointer
    // and set lights as output -> 0
    E = (volatile int*) 0xbf886100; // TRISE
    *E &= ~0xff;

    // You should use your own volatile pointer. 
    // Register PORTE has address 0xbf886110
    // and initialize the value of lights to 0
    E = (volatile int*) 0xbf886110; // PORTE
    *E = 15;
}

void setup_user_inputs() {
    // Initialize port D, set bits 11-5 as inputs.
    // same principle as above, bits that are "1" are inputs
    TRISDSET = 0xfe0;
	TRISFSET = 0x2; //Button 1

	TRISDSET = 0xf; // PLAYER 2 INPUTS: Chipkit pin 3, 5, 6  & 9 -> RD0->RD3
}

void setup_clock() {
    T2CONSET = 0x70; // Set the prescaler to 256.
    PR2 = (80000000 / 256) / 10; // Set timer max
    TMR2 = 0; // Set timer initial value
    T2CONSET = 0x8000;  // Start timer 2


    TMR1 = 0x0; // Clear timer register
    T1CONSET = 0x0070; // Set prescaler 1:256
    PR1 = 0x7FFF; // Load period register
    T1CONSET = 0x8000; // Start timer


    // Enable interrupts from TMR2
    IPCSET(2) = 0b100; // Interrupt Priority Control bit (IPC2<4:2>)
    IECSET(0) = 0x100; // Interrupt Enable Control, TEMPORARY DISABLE

    // Enable interrupt for Switch 1 (INT1)
    IECSET(0) = 0x1 << 7;
    IPCSET(1) = 0x1 << 27;

    /* Maybe remove
    // Enable interrupt for Switch 2 (INT2)
    IECSET(0) = 0x1 << 11;
    IPCSET(1) = 0x1 << 27;

    // Enable interrupt for Switch 3 (INT3)
    IECSET(0) = 0x1 << 15;
    IPCSET(1) = 0x1 << 27;

    // Enable interrupt for Switch 4 (INT4)
    IECSET(0) = 0x1 << 19;
    IPCSET(1) = 0x1 << 27;
    */


    // IEC 8th bit enables Timer 2 according to MIPS ref sheet (p. 90): 
    // For both IEC and IPC:
    // http://ww1.microchip.com/downloads/en/DeviceDoc/61143H.pdf

    // Enable interrupts globally
    enable_interrupt();
}