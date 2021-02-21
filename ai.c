#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

char get_AI_direction() {

    if (player2.y[0] > apple.y && player2.direction != 'd') // AI is below apple
        return 'u';
    if (player2.y[0] < apple.y && player2.direction != 'u') // AI is above apple
        return 'd';
    if (player2.x[0] < apple.x && player2.direction != 'l') // AI is to the left of apple
        return 'r';
    if (player2.x[0] > apple.x && player2.direction != 'r') // AI is to the right of apple
        return 'l';


    /* MACHINE LEARNING AI */

    if (player2.y[0] > apple.y && player2.direction == 'd') // AI is below apple and going down
        if (TMR1 % 10 < 5) return 'r';
        else return 'l';

    if (player2.y[0] < apple.y && player2.direction == 'u') // AI is above apple and going up
        if (TMR1 % 10 < 5) return 'r';
        else return 'l';
        
    if (player2.x[0] < apple.x && player2.direction == 'l') // AI is to the left of apple and going left
        if (TMR1 % 10 < 5) return 'u';
        else return 'd';
    
    if (player2.x[0] > apple.x && player2.direction == 'r') // AI is to the right of apple and going right
        if (TMR1 % 10 < 5) return 'u';
        else return 'd';
}


