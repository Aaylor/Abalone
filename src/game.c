#include "game.h"

int play_game(int b_player_statut, int n_player_statut, int test_mode, int load_game)
{
    /*  Test mode will be included after... */

    board *game_board = (board *)malloc(sizeof(board));

    if (load_game)
    {
        /*  Load the game_board and every game information here ... */
    }
    else
    {
        init_board(game_board);
    }

    display_board(game_board);
    return 0;
}

