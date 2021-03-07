/************************************************************

         Very Advanced Snake on Very Small Display

A game by Kalle Elmdahl and Erik Malm, developed in the KTH 
course IS1200 during spring 2021.

~~~~~~~~~~~~~~~~~~~~~~~~~~~  ai.c ~~~~~~~~~~~~~~~~~~~~~~~~~~~

Kalle is the main author of ai.c

The AI mode is essentially a 2 player game mode, where player 2
is controlled by the ChipKIT.

ai.c contains the functions that calculates the best
possible path for the ai to assume in order to avoid obstacles
and still chase the apples in the game.

************************************************************/

#include <stdint.h>
#include <pic32mx.h>
#include "snake.h"

uint8_t path_x[50];
uint8_t path_y[50];
char path_dir[50];
uint8_t ai_debug = 0;
uint8_t path_length = 0;
uint8_t current_pos_in_path = 0;
int index_of_obstruction = -1;
char possible_dirs[3];

void generate_path(int from_index);
int collision_pos();
char get_next_direction(uint8_t x, uint8_t y);
void add_path_block(char dir, uint8_t last_x, uint8_t last_y);
void get_possible_dirs(char last_dir);
void remove_killing_dirs(uint8_t last_x, uint8_t last_y);
char get_wanted_direction(uint8_t x, uint8_t y);
int is_valid_pos(uint8_t x, uint8_t y);
int is_valid_move(char *possible_dirs, char dir);
int get_next_x(char dir, uint8_t x);
int get_next_y(char dir, uint8_t y);
void draw_ai_path();

void init_ai() {
    path_length = 0;
    current_pos_in_path = 0;
    index_of_obstruction = -1;
}

void check_ai_path() {
    int index_of_collision = collision_pos();
    if(current_pos_in_path == path_length || current_pos_in_path == 40) {
        generate_path(-1); // generate new path to apple or extend current one
        current_pos_in_path = -1;
    } else if(index_of_collision != -1) {
        generate_path(-1);
        current_pos_in_path = -1;
    } else if(index_of_obstruction > 0) {
        generate_path(-1); // Path is not the most efficient try to find a better one
        current_pos_in_path = -1;
    } 
    current_pos_in_path++;
        
    player2.next_direction = path_dir[current_pos_in_path];


    if(ai_debug) draw_ai_path();
}

void generate_path(int from_index) {
    char last_dir = from_index == -1 ? player2.direction : path_dir[from_index];
    uint8_t last_x = from_index == -1 ? player2.x[0] : path_x[from_index];
    uint8_t last_y = from_index == -1 ? player2.y[0] : path_y[from_index];
    path_length = from_index;
    index_of_obstruction = -1;
    do {
        // Create a path
        path_length++;
        if(path_length == 50) break; // Don't create a path that is too long

        get_possible_dirs(last_dir);
        remove_killing_dirs(last_x, last_y); // removes directions resulting in death and returns 1 if any direction did
        if(possible_dirs[0] == 0) { // Snake is not able to move anywhere
            path_length--;
            break;
        }

        char next_direction = get_wanted_direction(last_x, last_y);

        if(!is_valid_move(possible_dirs, next_direction)) { // Prefered direction is not possible
            index_of_obstruction = path_length;
            next_direction = get_next_direction(last_x, last_y); // Get a smarter move
        }

        add_path_block(next_direction, last_x, last_y); 

        last_x = path_x[path_length];
        last_y = path_y[path_length];
        last_dir = path_dir[path_length];
        
    } while(last_x != apple.x || last_y != apple.y);
}

int collision_pos() {
    int i;
    for(i = current_pos_in_path + 1; i <= path_length; i++) {
        if(!is_valid_pos(path_x[i], path_y[i])) return i;
    }
    return -1;
}

char get_next_direction(uint8_t x, uint8_t y) {
    if(apple.x < x) {
        if(is_valid_move(possible_dirs, 'l')) return 'l';
        if(apple.y <= y && is_valid_move(possible_dirs, 'u')) return 'u';
        if(is_valid_move(possible_dirs, 'd')) return 'd';
        if(is_valid_move(possible_dirs, 'u')) return 'u';
        return 'r';
    } else if(apple.x > x) {
        if(is_valid_move(possible_dirs, 'r')) return 'r';
        if(apple.y <= y && is_valid_move(possible_dirs, 'u')) return 'u';
        if(is_valid_move(possible_dirs, 'd')) return 'd';
        if(is_valid_move(possible_dirs, 'u')) return 'u';
        return 'l';
    } else if(apple.y > y) {
        if(is_valid_move(possible_dirs, 'd')) return 'd';
        if(apple.x <= y && is_valid_move(possible_dirs, 'l')) return 'l';
        if(is_valid_move(possible_dirs, 'r')) return 'r';
        if(is_valid_move(possible_dirs, 'l')) return 'l';
        return 'u';
    } else {
        if(is_valid_move(possible_dirs, 'u')) return 'u';
        if(apple.x <= y && is_valid_move(possible_dirs, 'l')) return 'l';
        if(is_valid_move(possible_dirs, 'r')) return 'r';
        if(is_valid_move(possible_dirs, 'l')) return 'l';
        return 'd';
    }
}

void add_path_block(char dir, uint8_t last_x, uint8_t last_y) {
    path_dir[path_length] = dir;
    path_x[path_length] = get_next_x(dir, last_x);
    path_y[path_length] = get_next_y(dir, last_y);
}

void get_possible_dirs(char last_dir) {
    possible_dirs[0] = 'l'; // Set values for case u and change if its not u (kinda hacky)
    possible_dirs[1] = 'r';
    possible_dirs[2] = 'u';
    switch(last_dir) {
        case 'd':
            possible_dirs[2] = 'd';
            break;
        case 'l':
            possible_dirs[1] = 'd';
            break;
        case 'r':
            possible_dirs[0] = 'd';
            break;
    }
}

void remove_killing_dirs(uint8_t last_x, uint8_t last_y) {
    int i, j = 2;
    for(i = 0; i <= j; i++) {
        if(!is_valid_pos(get_next_x(possible_dirs[i], last_x), get_next_y(possible_dirs[i], last_y))) {
            possible_dirs[i] = possible_dirs[j]; // remove direction at index and move other dir forwards
            possible_dirs[j--] = 0;
            i--;
        }
    }
}

char get_wanted_direction(uint8_t x, uint8_t y) {
    if(apple.x < x) return 'l';
    else if(apple.x > x) return 'r';
    else if(apple.y > y) return 'd';
    else return 'u';
}

int is_valid_pos(uint8_t x, uint8_t y) {
    int j;
    if( x < 1 || 
        y < 1 || 
        x + SNAKE_SIZE > DISPLAY_WIDTH - SIDEBAR_WIDTH || 
        y + SNAKE_SIZE > DISPLAY_HEIGHT) return 0; // Snake is outside of world
    

    for(j = 3; j < player2.length; j++)
        if(x == player2.x[j] && y == player2.y[j]) return 0; // Snake is colliding with itself

    for(j = 0; j < player1.length; j++)
        if(x == player1.x[j] && y == player1.y[j]) return 0; // Path is colliding with player 1
    return 1;
}

int is_valid_move(char *possible_dirs, char dir) {
    int i;
    for(i = 0; i < 3; i++) if(possible_dirs[i] == dir) return 1;
    return 0;
}

int get_next_x(char dir, uint8_t x) {
    switch(dir) {
        case 'l':
            x -= SNAKE_SIZE;
            break;
        case 'r':
            x += SNAKE_SIZE;
            break;
    }
    return x;
}

int get_next_y(char dir, uint8_t y) {
    switch(dir) {
        case 'u':
            y -= SNAKE_SIZE;
            break;
        case 'd':
            y += SNAKE_SIZE;
            break;
    }
    return y;
}

void draw_ai_path() {
    int i;    
    for(i = 0; i < path_length; i++) { // first index will already be used when drawing snake
        if(path_dir[i] == 'u' || path_dir[i] == 'd')  draw_rect(path_x[i] + 1, path_y[i], 1, 3);
        else draw_rect(path_x[i], path_y[i] + 1, 3, 1);
    }
}