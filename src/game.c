#include "game.h"

int play_game(int b_player_statut, int n_player_statut, int test_mode, int load_game)
{
    /*  Test mode will be included after... */
    board   *game_board = (board *)malloc(sizeof(board));
    char    *command = malloc(CMD_MAX_SIZE * sizeof(char));
    int     coup = 1;

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
        char current_player = (coup & 1 ? 'B' : 'N');
        char *prompt = (current_player == 'B' ? PROMPT_B : PROMPT_N);

        if ( (current_player == 'B' && b_player_statut) ||
             (current_player == 'N' && n_player_statut))
        {
            if (!test_mode)
                fprintf(stdout, "#%d %s", coup, prompt);
            if (fscanf(stdin, "%s", command) == EOF)
                return 1;
        }
        else
        {
            fprintf(stdout, "faire jouer l'ia ici... *visible par la variable current_player*\n");
        }

        /*
         *  Tester la validité de la commande ici. (Correspond aux critères
         *  demandés).
         *  Tester la possibilité du mouvement.
         *  Effectuer les mouvements.
         *  Changer les états de certaines variables (notamment au niveau des
         *  jetons sortis).
         *  Vérifier si il y a un gagnant.
         */
        printf("commande : %s\n", command);

        coup++;
    }
    
    return 0;
}

