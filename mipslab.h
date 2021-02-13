/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */


uint8_t dxsnake;
uint8_t dysnake;

volatile int* E;


/* setup.c */
void setup_ports( void );
void setup_display( void );

/* game.c */
void game_init( void );
void game_update( void );

/* io.c */
void check_buttons();

/* main.c */
extern uint8_t pixels[32][128];
void update( void );

/* util.c */
void update_display( void );
uint8_t spi_send_recv(uint8_t data);
void quicksleep(int cyc);

/* interrupt.S */
void enable_interrupt(void);