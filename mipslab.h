/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

/* Display */
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 32
#define DISPLAY_ROWS 4
#define DISPLAY_ROW_HEIGHT DISPLAY_HEIGHT / DISPLAY_ROWS

/* Text */
#define CHAR_WIDTH 7


uint8_t dxsnake;
uint8_t dysnake;
/* Enumerator for different parts of the appliceation */
enum app_states {StartPage, Menu, Game} app_state;
enum app_states app_state;

/* setup.c */
void setup_ports( void );
void setup_display( void );

volatile int* E;
void setup_leds( void );
void setup_user_inputs( void );
void setup_clock( void );

/* game.c */
void game_init( void );
void game_update( void );

/* io.c */
void check_buttons();

/* main.c */
extern uint8_t pixels[DISPLAY_HEIGHT][DISPLAY_WIDTH];
void update( void );

/* util.c */
void update_display( void );
void clear_pixels();
uint8_t spi_send_recv(uint8_t data);
void quicksleep(int cyc);

void draw_text(int x, int y, char *s);
void draw_rect(int x, int y, int w, int h);

/* interrupt.S */
void enable_interrupt(void);

/* data.c */
extern uint8_t text[DISPLAY_ROWS][DISPLAY_WIDTH];
extern const uint8_t const font[128][CHAR_WIDTH];