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
#define SCREEN_CENTER (MAX_X - SIDEBAR_WIDTH) / 2

/* Text */
#define CHAR_WIDTH 7

/* Enumerator for different parts of the appliceation */
enum app_states {START_PAGE, MENU, SUB_MENU, GAME} app_state;
enum app_states app_state;

enum game_states {IN_GAME, GAME_OVER, WRITING_HIGHSCORE} game_state;
enum game_states game_state;

enum game_modes {ONE_PLAYER, TWO_PLAYER, AI} game_mode;
enum game_modes game_mode;

enum game_speeds {FAST, NORMAL, SLOW} game_speed;
enum game_speeds game_speed;

enum sub_menus {GAME_MODE, SPEED, CREDITS, HIGHSCORE} current_sub_menu;
enum sub_menus current_sub_menu;

/* Global variables */
uint8_t player_1x [120]; // Initalize array outside of struct because reasons
uint8_t player_1y [120]; // Initalize array outside of struct because reasons
uint8_t player_2x [120]; // Initalize array outside of struct because reasons
uint8_t player_2y [120]; // Initalize array outside of struct because reasons
char memory_write_data[12]; // Assign chars to be written to memory
char memory_read_data[12]; // Read chars will end up in this array

/* setup.c */
void setup_ports( void );
void setup_display( void );

volatile int* E;
void setup_leds( void );
void setup_user_inputs( void );
void setup_clock( void );
void i2c_init( void);

/* game.c */
struct Snake player1;
struct Snake player2;
struct Apple apple;
struct Obstacle obstacle;
void game_init( void );
void game_update( void );

extern int selected_initial;
char initials[3];

/* snake.c */
#define SNAKE_WIDTH 3 // Defines the width of the snake
#define SNAKE_SIZE 3 // Defines size of snake body-block

struct Snake { 
    uint8_t *x;
    uint8_t *y;
    char direction; // l = left, u = up, d = down, r = right
    char next_direction; // l = left, u = up, d = down, r = right
    uint8_t should_grow;
    int length;
};

/* ai.c */
char get_AI_direction();

struct Snake initialize_snake( uint8_t );
void display_snake(struct Snake);
struct Snake update_snake(struct Snake, struct Snake);

/* Apple.c */
void new_apple( void );
void display_apple( void );
int is_eating(struct Snake);
struct Apple { 
    uint8_t x;
    uint8_t y;
};

/* Obstacles.c */
void new_obstacle ( void );
void display_obstacle ( void );
struct Obstacle { 
    uint8_t x;
    uint8_t y;
    uint8_t animation;
};

/* io.c */
int check_user_inputs();

/* main.c */
extern uint8_t pixels[DISPLAY_HEIGHT][DISPLAY_WIDTH];
void update( void );
extern int game_update_time;

/* menu.c */
void draw_menu( void );
void select_current_menu_item( void );
struct menu_item {
    char *text;
    int text_width;
    int sub_menu;
    int action;
};
extern int current_menu_position;
#define number_of_menu_items 5

/* submenu.c */
void init_sub_menu( void );
void draw_sub_menu( void );
void update_sub_menu(int btns);
void draw_highscore();

/* startpage.c */
void draw_start_page( void );

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
const uint8_t const arrow_right[5][3];
const uint8_t const arrow_left[5][3];
const uint8_t const arrow_up[3][5];
const uint8_t const arrow_down[3][5];
const uint8_t const apple_icon[3][3];
const uint8_t const check_box[5][6];
const uint8_t const sq_obstacle[5][5];
const uint8_t const sq_obstacle_animation[5][5];

/* highscore.c */
struct highscore {
    int score;
    char first_name;
    char last_name;
};
void save_highscore_to_memory( void );
struct highscore highscores[3]; 

void init_higscores( void );

/* memory.c */

void write_to_memory( char* write_data, int memory_address, int len ); // Will write the contents of char[] write_to_memory to (short address) for the amount (int len)
void read_from_memory( int memory_address, int len ); // Will read the contents of address for the amount (int len)
void clear_memory_data();
void clear_highscore_memory();