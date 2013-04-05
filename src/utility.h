#ifndef H_UTILITY
#define H_UTILITY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_LENGTH 9


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

#endif

