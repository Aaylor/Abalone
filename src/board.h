#ifndef H_BOARD
#define H_BOARD

typedef struct
{
    char tab[BOARD_LENGTH][BOARD_LENGTH];
} board;

board init_new_board();
void display_board(board *b);
int min_col(char l);
int max_col(char l);

#endif
