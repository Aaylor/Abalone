#ifndef H_MAIN
#define H_MAIN

#include "utility.h"
#include "game.h"

/*
 *  parse every arguments given by the user when starting the program, where :
 *      -B <type> give the type (human or robot) to the white player
 *      -N <type> give the type (human or robot) to the black player
 *      -c <filename> load the game from the file given by the user
 *      -t use test mode
 */
int parse_arguments(int, char **, int *, int *, int *, int *, char **);

#endif

