#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

char preferred_direction();
char check_for_coming_collision();
int check_for_collision(int pos);
char new_direction;

char get_AI_direction() {
    new_direction = preferred_direction();
    new_direction = check_for_coming_collision();
    return new_direction;
}

char preferred_direction() {
    if (player2.y[0] > apple.y && player2.direction != 'd') // AI is below apple
        return 'u';
    if (player2.y[0] < apple.y && player2.direction != 'u') // AI is above apple
        return 'd';
    if (player2.x[0] < apple.x && player2.direction != 'l') // AI is to the left of apple
        return 'r';
    if (player2.x[0] > apple.x && player2.direction != 'r') // AI is to the right of apple
        return 'l';


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

    else
        return player2.direction;
}

char check_for_coming_collision() {

    int i;
    int steps = 3 * SNAKE_SIZE; // Steps to check
    int posx = player2.x[0]; // Check for player position X
    int posy = player2.y[0]; // Check for player position Y

    if (new_direction == 'u') // AI is going up
        if (check_for_collision_with_snakes(posy - SNAKE_SIZE)) {
            if (check_for_collision_with_snakes(posx + SNAKE_SIZE)) 
                return 'l';
            else
                return 'r';
        }

    if (new_direction == 'd') // AI is going down
        if (check_for_collision_with_snakes(posy + SNAKE_SIZE)) {
            if (check_for_collision_with_snakes(posx + SNAKE_SIZE)) 
                return 'l';
            else
                return 'r';
        }

    if (new_direction == 'l') // AI is going left
        if (check_for_collision_with_snakes(posx - SNAKE_SIZE)) {
            if (check_for_collision_with_snakes(posy + SNAKE_SIZE)) 
                return 'u';
            else
                return 'd';
        }

    if (new_direction == 'r') // AI is going right
        if (check_for_collision_with_snakes(posx + SNAKE_SIZE)) {
            if (check_for_collision_with_snakes(posy + SNAKE_SIZE)) 
                return 'u';
            else
                return 'd';
        }
    /*

    if (new_direction == 'u') // AI is going up
        for (i = posy - SNAKE_SIZE; i > posy - steps; i -= SNAKE_SIZE) 
            if (check_for_collision_with_snakes(i)) {
                if (check_for_collision_with_snakes(posx + SNAKE_SIZE)) // Check for collision with other player if going right
                    return 'l'; // Collision detected, go left
                else
                    return 'r'; // No collision with other player detected, go right 
            }

    if (new_direction == 'd') // AI is going down
        for (i = posy + SNAKE_SIZE; i > posy + steps; i += SNAKE_SIZE) 
            if (check_for_collision_with_snakes(i)) {
                if (check_for_collision_with_snakes(posx + SNAKE_SIZE)) // Check for collision with other player if going right
                    return 'l'; // Collision detected, go left
                else
                    return 'r'; // No collision with other player detected, go right 
            }

    if (new_direction == 'r') // AI is going right
        for (i = posx + SNAKE_SIZE; i < posx + steps; i += SNAKE_SIZE)
            if (check_for_collision_with_snakes(i)) {
                if (check_for_collision_with_snakes(posy + SNAKE_SIZE)) // Check for collision with other player if going down
                    return 'u'; // Collision detected, go up
                else
                    return 'd'; // No collision with other player detected, go down
            }

    if (new_direction == 'l') // AI is going left
        for (i = posx - SNAKE_SIZE; i > posx - steps; i -= SNAKE_SIZE)
            if (check_for_collision_with_snakes(i)) {
                if (check_for_collision_with_snakes(posy + SNAKE_SIZE)) // Check for collision with other player if going down
                    return 'u'; // Collision detected, go up
                else
                    return 'd'; // No collision with other player detected, go down
            }

            */

    return new_direction;
}

int check_for_collision_with_snakes(int pos) {
    
    int i;

    for (i = 0; i <= player1.length; i ++) // Check for collision with other player
        if(pos == player1.x[i] && player1.y[i] == pos)  // Collision detected with player 1, change direction and return
            return 1;

    for (i = 0; i <= player2.length; i ++) // Check for collision with self
        if(pos == player2.x[i] && player2.y[i] == pos)  // Collision detected with player 1, change direction and return
            return 1;

    return 0;
}
        

