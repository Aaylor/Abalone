#ifndef H_UTILITY
#define H_UTILITY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LATERAL_MOVEMENT_POSSIBLE 1
#define LINE_MOVEMENT_POSSIBLE 2
#define NOT_POSSIBLE_NO_PLAYER_MARBLE -1
#define NOT_POSSIBLE_SQUARES_IDENTICAL -2
#define NOT_POSSIBLE_SQUARES_NON_ADJACENT -3
#define NOT_POSSIBLE_SQUARES_NON_ALIGNED -4
#define NOT_POSSIBLE_ARRIVAL_SQUARE_NOT_EMPTY -5
#define NOT_POSSIBLE_TOO_MUCH_RIVAL_MARBLES -7
#define NOT_POSSIBLE_TOO_MUCH_PLAYER_MARBLES -8
#define NOT_POSSIBLE_EGAL_PLAYER_AND_RIVAL_MARBLES -9
#define NOT_POSSIBLE_MORE_RIVAL_MARBLES_THAN_PLAYER -10
#define NOT_POSSIBLE_SQUARE_HAS_NO_SENS -11
#define NOT_POSSIBLE_PLAYER_MARBLE_EJECTION -12
#define NOT_POSSIBLE_FOR_NO_REASON -666
#define POSSIBLE_FOR_NO_REASON 666

#define BOARD_LENGTH 9

#define player char

#define H_PLAYER    0x000000f
#define VERY_EASY_AI     0x00000f0

/*
 *  Give the int value associated to the character to match to keys of the
 *  board.tab
 */
#define c_to_key(character) (character - 'A')

/*
 *  Give the key according to the integer value given by the user
 */
#define i_to_key(integer) (integer - 1)

/*
 *  Give the character according to the board key
 */
#define key_to_c(integer) (integer + 'A')

/*
 *  Give the integer according to the board key
 */
#define key_to_i(integer) (integer + 1)

/*
 *  It's use to get a better understanding using strcmp function.
 *  Instead of returning 0 if the two strings are equals, it'll return 1.
 */
#define str_cmp(s1,s2) (strcmp(s1,s2) == 0)

/*
 *  Return a random number, to chose random move for ai.
 */
#define get_random_num(max) (rand()%max)

/*
 *  Set the color text.
 */
#define set_colot_text(param) printf("\033[%sm",param)

typedef struct
{
    char **squares;
    int length;
    player color;
} p_move;

#endif
