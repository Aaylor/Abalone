#include "game.h"

int play_game(int b_player_statut, int n_player_statut, int test_mode, int load_game)
{
    /*  Test mode will be included after... */

    board   *game_board = (board *)malloc(sizeof(board));
    char    *command = malloc(CMD_MAX_SIZE * sizeof(char));

    if (load_game)
    {
        /*  Load the game_board and every game information here ... */
    }
    else
    {
        init_board(game_board);
    }

    while( 1 )
    {
        display_board(game_board);
        
        /*
         * GERER PLAYER [AI ?]
         * GERER COMMANDES
         */
        fprintf(stdout, PROMPT_B);
        fscanf(stdin, "%s", command);
        printf("%s\n", command);

        break;
    }
    
    return 0;
}

