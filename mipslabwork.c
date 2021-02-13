/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall
   This file modified 2017-04-31 by Ture Teknolog 
   Updated 2021-02-10 by E Malm

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5953;
int timeoutcount = 0;
int prime = 1234567;

// You should use your own volatile pointer.
volatile int* E;
volatile int* D;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void ) { 


  /*
  In file mipslabwork.c, add code into the function user_isr 
  to acknowledge interrupts from Timer 2. 
  Note that function user_isr should include the code that is called 
  every time an interrupt occurs. It should not include the code 
  that initializes the interrupt routine.
  */

	if (IFS(0) & 0x100) {

		timeoutcount++;
		IFS(0) = 0;
	
  /*
   In file mipslabwork.c, change function user_isr to update and check 
   the global counter timeoutcount, so that that time2string, display_string, 
   display_update and tick are only called once in 10 invocations of user_isr.
  */
		if (timeoutcount == 10) {

            time2string(textstring, mytime);
            display_string(3, textstring);
            display_update();
            tick( &mytime);
            timeoutcount = 0;
            *E += 1; // increment led pointer
		}

	}

}

/* Lab-specific initialization goes here */
void labinit( void )
{
  
    // Register TRISE has address 0xbf886100
    // initialize the port using your own volatile pointer
    // and set lights as output -> 0
    E = (volatile int*) 0xbf886100; // TRISE
    *E &= ~0xff;

    // You should use your own volatile pointer. 
    // Register PORTE has address 0xbf886110
    // and initialize the value of lights to 0
    E = (volatile int*) 0xbf886110; // PORTE
    *E = 0;

    // Initialize port D, set bits 11-5 as inputs.
    // same principle as above, bits that are "1" are inputs
    // TRISD is accessed via our volatile pointer D
    // 1111 1110 0000 <- 0x7f0
    // D = (volatile int*)(TRISD << 3); 
    // *D |= 0xfe0; //Set inputs to TRISD

    TRISD |= 0xfe0;


    // Timer stuff

    T2CONSET = 0x70; // Set the prescaler to 256.

    // In file mipslabwork.c, add code to initialize Timer 2 
    // for timeouts every 100 ms (that is 10 time-outs per second). 
    // Be prepared to justify  your choices of clock-rate divider and time-out period.
    // 80 Mhz / The clock signal is divided by 128 in the prescaler

    // TMR2 operates at vector / natural order 8, 2^8 = 256 probably wrong
    // we want the period to be 1/10 of a second.
    PR2 = (80000000 / 256) / 10;
    TMR2 = 0;   // We want TMR2 to begin at 0

    // The ON bit is bit 15 in T2CON, and can be set to ’1’
    T2CONSET = 0x8000;  // Start 32-bit timer http://ww1.microchip.com/downloads/en/devicedoc/61105f.pdf


    /* 
    add code to the function labinit, to enable interrupts from Timer 2, 
    and of course to enable interrupts globally. Before enabling interrupts globally, 
    all other initialization must be complete. 

    Note: IEC(0) is at 0xbf881060, and IPC(2) at 0xbf8810b0.

    */ 
    // assignment 3
    // Enable interrupts from TMR2
    IPCSET(2) = 0b100; // Interrupt Priority Control bit (IPC2<4:2>)
    IECSET(0) = 0x100; // Interrupt Enable Control, 
    // IEC 8th bit enables Timer 2 according to MIPS ref sheet (p. 90): 
    // For both IEC and IPC:
    // http://ww1.microchip.com/downloads/en/DeviceDoc/61143H.pdf

    /* surprise assignment
    // Enable interrupts for SW3
    IPC(3) = 0x1c000000;
    IEC(0) = IEC(0) | (1 << 15);	
    */


    // Enable interrupts globally
    enable_interrupt();

    return;
}

/* This function is called repetitively from the main program */
void labwork( void ) {  
  // display_string( 0, itoaconv( prime ) );  
  display_update();
  // display_debug(IEC(0));
}
