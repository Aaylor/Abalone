#ifndef H_BOARD
#define H_BOARD

#include "utility.h"

typedef struct
{
    char tab[BOARD_LENGTH][BOARD_LENGTH];
  int ejected_marble_B;
  int ejected_marble_N;
} board;

board create_new_board();
board *init_board(board*b);
void display_board(board *b);
int min_col(char l);
int max_col(char l);
int marbles_alignement(char **tab, int tabLen);
int marbles_are_adjacent(char **tab, int tabLen);
int what_marble_does_move_ejects(board *b, p_move* commande);
void do_move(board *b, p_move *commande);
int move_is_possible(board *b, p_move *commande);
p_move* possible_movements(board *b, player couleur, int *length);


#endif
