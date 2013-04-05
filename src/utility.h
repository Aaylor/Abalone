#ifndef H_UTILITY
#define H_UTILITY

#include <stdio.h>
#include <stdlib.h>

#define BOARD_LENGTH 9

/*
 *  Return the int value associated to the character to match to keys of the
 *  board.tab
 */
#define c_to_key(character) (character - 'A')
#define i_to_key(integer) (integer - 1)
#define key_to_c(integer) (integer + 'A')
#define key_to_i(integer) (integer + 1)

#endif

