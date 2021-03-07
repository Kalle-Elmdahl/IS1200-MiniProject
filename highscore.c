#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "snake.h"  /* Declarations for game */

 // Highscore positions are located at three different addresses.
 // 1:st position at 0x1000
 // 2:nd position at 0x2000
 // 3:rd position at 0x3000
 int highscore_address[3] = {0x1000, 0x2000, 0x3000};


void save_highscore(char *letters, int score) {

    init_higscores();

    int i, j;
    for (i = 0; i < 3; i ++) {
        if (highscores[i].score < score) {
            for(j = 2; j >= i; j--) {
                highscores[j] = highscores[j - 1];
            }
            highscores[i].score = score;
            highscores[i].first_letter = letters[0];
            highscores[i].second_letter = letters[1];
            highscores[i].third_letter = letters[2];
            break;
        }
    }
    save_highscore_to_memory();
}

void init_higscores( void ){

    int i;
    
    for (i = 0; i < 3; i ++) {
        read_from_memory(highscore_address[i], 4);
        
        highscores[i].first_letter = memory_read_data[0];
        highscores[i].second_letter = memory_read_data[1];
        highscores[i].third_letter = memory_read_data[2];
        highscores[i].score = memory_read_data[3];
    }
}

void save_highscore_to_memory() {

    int i;
    
    for (i = 0; i < 3; i ++) {

        char highscore_to_save[3];
        highscore_to_save[0] = highscores[i].first_letter;
        highscore_to_save[1] = highscores[i].second_letter;
        highscore_to_save[2] = highscores[i].third_letter;
        highscore_to_save[3] = highscores[i].score;

        write_to_memory(highscore_to_save, highscore_address[i], 4);
    }
}