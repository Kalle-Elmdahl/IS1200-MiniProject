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
#define MAX_X 127
#define MAX_Y 31

/* UI */
#define SIDEBAR_WIDTH 25

/* Text */
#define CHAR_WIDTH 7

/* Enumerator for different parts of the appliceation */
enum app_states {START_PAGE, MENU, GAME} app_state;
enum app_states app_state;

enum game_states {IN_GAME, GAME_OVER} game_state;
enum game_states game_state;

/* setup.c */
void setup_ports( void );
void setup_display( void );

volatile int* E;
void setup_leds( void );
void setup_user_inputs( void );
void setup_clock( void );

/* game.c */
struct Snake player1;
struct Apple apple;
void game_init( void );
void game_update( void );
void game_over( void );

/* snake.c */
#define SNAKE_WIDTH 3 // Defines the width of the snake
#define SNAKE_SIZE 3 // Defines size of snake body-block
struct Snake_Body {
    int x, y;
};

uint8_t player_1x [24]; // Initalize array outside of struct because of reasons

struct Snake { 
    uint8_t *x;
    uint8_t y [12];
    uint8_t direction; // Bits 0->3: Left, Up, Down, Right
    uint8_t next_direction; // Bits 0->3: Left, Up, Down, Right
    uint8_t should_grow;
    int length;
};

struct Snake initialize_snake();
void display_snake(struct Snake);
struct Snake update_snake(struct Snake);

/* Apple.c */
void new_apple( void );
void display_apple( void );
int is_eating(struct Snake);
struct Apple { 
    uint8_t x;
    uint8_t y;
};

/* io.c */
void check_buttons();

/* main.c */
extern uint8_t pixels[DISPLAY_HEIGHT][DISPLAY_WIDTH];
void update( void );

/* menu.c */
void draw_menu( void );

/* startpage.c */
void draw_start_page();

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
extern const uint8_t const lever_up[16][9];
extern const uint8_t const lever_down[16][9];
const uint8_t const apple_icon[3][3];