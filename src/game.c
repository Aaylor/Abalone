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
        regfree(&preg);

        return (match == 0 ? MATCH : DONT_MATCH);
    }

    return -1;
}

char **split_command(char *command, int *command_length)
{
    char *tmp_command = strcpy(malloc((strlen(command) + 1) * sizeof(char)), command);
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
        *(splitted_command + i) = strcpy(malloc((strlen(token) + 1) * sizeof(char)), token);
        i++;
    }
    while ((token = strtok(NULL, "-")) != NULL)
    {
        *(splitted_command + i) = strcpy(malloc((strlen(token) + 1) * sizeof(char)), token);
        i++;
    }

    free(token);
    free(tmp_command);

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
        
        *reworked_command = strcpy(malloc(((strlen(*(splitted_command)) + 1) * sizeof(char))), *(splitted_command));
        char *last = strcpy(malloc(((strlen(*(splitted_command + 1)) + 1) * sizeof(char))), *(splitted_command + 1));

        int i = 1;
        for (; i < max_length - 1; i++)
        {
            char *tmp = malloc(2 * sizeof(char));
            if (reworked_command[i-1][0] > last[0])
                *tmp = reworked_command[i-1][0] - 1;
            else if (reworked_command[i-1][0] < last[0])
                *tmp = reworked_command[i-1][0] + 1;
            else
                *tmp = reworked_command[i-1][0];

            if (reworked_command[i-1][1] > last[1])
                *(tmp + 1) = reworked_command[i-1][1] - 1;
            else if (reworked_command[i-1][1] < last[1])
                *(tmp + 1) = reworked_command[i-1][1] + 1;
            else
                *(tmp + 1) = reworked_command[i-1][1];
            
            reworked_command[i] = tmp;
        }
        *(reworked_command + i) = last;

        int j = 0;
        int x = splitted_command[2][0] - reworked_command[0][0];
        int y = splitted_command[2][1] - reworked_command[0][1];
        i++;
        for (; i < 2 * max_length; i++)
        {
            char *tmp = malloc(2 * sizeof(char));
            *tmp = reworked_command[j][0] + x;
            *(tmp + 1) = reworked_command[j][1] + y;

            reworked_command[i] = tmp;
            j++;
        }

        free(splitted_command);

        *length = 2 * max_length;
        return reworked_command;
    }
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
            char **new_command = rework_move(command, &length);
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

