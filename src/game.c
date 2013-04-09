#include "game.h"

int command_validation(const char *command)
{
    int err_num;
    regex_t preg;
   
    const char *regex = "^\\([A-I][1-9]-\\)\\{1,2\\}[A-I][1-9]$";

    err_num = regcomp(&preg, regex, REG_NOSUB | REG_ICASE);
    if (err_num == 0)
    {
        int match = regexec(&preg, command, 0, NULL, 0);

        return (match == 0 ? MATCH : DONT_MATCH);
    }

    return -1;
}

char **split_command(char *command, int *command_length)
{
    char *tmp_command = strdup(command);
    int i = 0;
    int count_character = 0;

    for (i = 0; *(tmp_command + i); i++)
    {
        if (*(tmp_command + i) == '-')
            count_character++;
    }

    i = 0;
    char **splitted_command = malloc((count_character + 1) * sizeof(char *));

    char *token = strtok(tmp_command, "-");
    if (token)
    {
        *(splitted_command + i) = strdup(token);
        i++;
    }
    while ((token = strtok(NULL, "-")) != NULL)
    {
        *(splitted_command + i) = strdup(token);
        i++;
    }

    *command_length = i;
    return splitted_command;
}

char **rework_move(char *command, int *length)
{
    int command_length = 0;
    char **splitted_command = split_command(command, &command_length);

    if (command_length == 2)
    {
        *length = command_length;
        return splitted_command;
    }
    else
    {
        int max_length = (abs(splitted_command[0][0] - splitted_command[1][0]) > abs(splitted_command[0][1] - splitted_command[1][1]) ?
                abs(splitted_command[0][0] - splitted_command[1][0]) + 1 : abs(splitted_command[0][1] - splitted_command[1][1]) + 1);
        char **reworked_command = malloc((2 * max_length) * sizeof(char *));
        
        *reworked_command = strdup(*(splitted_command));
        char *last = strdup(*(splitted_command+1));
        
        int i = 1;
        for (; i < max_length; i++)
        {
            char tmp[2];
            if (*(reworked_command-1)[0] > last[0])
            {
                tmp[0] = *(reworked_command)[0] - 1;
            }
        }
    }
    return NULL;
}

int play_game(int b_player_statut, int n_player_statut, int test_mode, int load_game)
{
    /*  Test mode will be included after... */
    board   *game_board = (board *)malloc(sizeof(board));
    char    *command = malloc((CMD_MAX_SIZE + 1) * sizeof(char));
    int     coup = 1;

    if (load_game)
    {
        /*  Load the game_board and every game information here ... */
    }
    else
    {
        init_board(game_board);
    }

    display_board(game_board);
    while( 1 )
    {
        int length = 0;
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
            continue;
        }

        
        if (str_cmp(command, "exit"))
            return 1;
        else if (0);
        else if (!command_validation(command))
        {
            fprintf(stderr, "WRONG COMMAND, PLAY AGAIN\n");
            continue;
        }
        else
        {
            /*char **splitted_command = split_command(command, &length);
            printf("%d\n", move_is_possible(game_board, splitted_command, length));*/
            char **new_command = rework_move(command, &length);
            int i = 0;
            for( ; i < length; i++)
            {
                fprintf(stdout, "CMD : %s\n", *(new_command+i));
            }
            printf("%d\n", move_is_possible(game_board, new_command, length));
            free(new_command);
            length = 0;
        }

        /*
         *  Tester la possibilité du mouvement.
         *  Effectuer les mouvements.
         *  Changer les états de certaines variables (notamment au niveau des
         *  jetons sortis).
         *  Vérifier si il y a un gagnant.
         */
        printf("commande : %s\n", command);
        display_board(game_board);

        coup++;
    }
    
    return 0;
}

