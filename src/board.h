#ifndef H_BOARD
#define H_BOARD

typedef struct
{
    char tab[BOARD_LENGTH][BOARD_LENGTH];
} board;

board init_new_board();
void display_board(board *b);

#endif
