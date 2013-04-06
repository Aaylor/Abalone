#ifndef H_BOARD
#define H_BOARD

#include "utility.h"

typedef struct
{
    char tab[BOARD_LENGTH][BOARD_LENGTH];
} board;

board create_new_board();
board *init_board(board*b);
void display_board(board *b);
int min_col(char l);
int max_col(char l);
int marbles_alignement(char **tab, int tabLen);
int marbles_are_adjacent(char **tab, int tabLen);

#endif
