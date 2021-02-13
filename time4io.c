#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h" 

int getsw( void ){

	// The four least significant bits of the return value 
	// should contain data from switches SW4, SW3, SW2, and SW1. 
	// SW1 corresponds to the least significant bit. 
	// All other bits of the returnvalue must be zero.

	// The function getsw will never be called before 
	// Port D has been correctly initialized. 
	// The switches SW4 through SW1 are connected to bits 11 through 8 of Port D.
	return (PORTD >> 8) & 0xF;
}

int getbtns(void){


	// The 3 least significant bits of the return value 
	// must contain current data from push buttons BTN4, BTN3, and BTN2. 
	// BTN2 corresponds to the least significant bit. 
	// All other bits of the return value must be zero.

	// The function getbtns will never be called before 
	// Port D has been correctly initialized. 
	// The buttons BTN4, BTN3, and BTN2, are connected to bits 7, 6 and 5 of Port D.
	return (PORTD >> 5) & 0x7;
}