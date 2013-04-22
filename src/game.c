#include "game.h"

int command_validation(const char *command)
{
    int         err_num, match;
    regex_t     preg;
    const char  *regex;
   
    regex = "^\\([A-I][1-9]-\\)\\{1,2\\}[A-I][1-9]$";
    err_num = regcomp(&preg, regex, REG_NOSUB | REG_ICASE);
    
    if (err_num == 0)
    {
        match = regexec(&preg, command, 0, NULL, 0);
        regfree(&preg);
        return (match == 0 ? MATCH : DONT_MATCH);
    }

    return -1;
}

char **split_command(char *command, int *command_length)
{
    int     i, count_character;
    char    *token, *tmp_command, **splitted_command; 
    
    if ((tmp_command = strcpy(malloc((strlen(command) + 1) * sizeof(char)), command)) == NULL)
        fprintf(stderr, "Erreur dans la copie...\n");
    
    count_character = 0;
    for (i = 0; *(tmp_command + i); i++)
    {
        if (*(tmp_command + i) == '-')
            count_character++;
    }

    i = 0;
    splitted_command = malloc((count_character + 1) * sizeof(char *));
    token = strtok(tmp_command, "-");
    if (token)
    {
        /*
        if ((*(splitted_command + i) = strcpy(malloc((strlen(token) + 1) * sizeof(char)), token)) == NULL)
            fprintf(stderr, "Erreur dans la copie du token...\n"); */
        *(splitted_command + i) = strcpy(malloc((strlen(token) + 1) * sizeof(char)), token);
        i++;
    }
    while ((token = strtok(NULL, "-")) != NULL)
    {
        if ((*(splitted_command + i) = strcpy(malloc((strlen(token) + 1) * sizeof(char)), token)) == NULL)
            fprintf(stderr, "Erreur dans la copie du token...\n");
        i++;
    }

    free(token); token = NULL;
    free(tmp_command); tmp_command = NULL;
    
    *command_length = i;
    return splitted_command;
}

p_move *rework_move(char *command)
{
    int i, j, x, y;
    
    int command_length = 0;
    p_move *n_command = malloc(sizeof(p_move));
    char **splitted_command = split_command(command, &command_length);

    if (command_length == 2)
    {
        n_command->squares = splitted_command;
        n_command->length = command_length;
        return n_command;
    }
    else
    {
        char *last;
        
        int max_length = (abs(**splitted_command - *(*(splitted_command + 1))) > abs(*(*splitted_command + 1) - *(*(splitted_command + 1) + 1)) ?
                abs(**splitted_command - *(*(splitted_command + 1))) + 1 : abs(*(*splitted_command + 1) - *(*(splitted_command + 1) + 1)) + 1);
        char **reworked_command = malloc((2 * max_length) * sizeof(char *));
        
        if ((last = strcpy(malloc(((strlen(*(splitted_command + 1)) + 1) * sizeof(char))), *(splitted_command + 1))) == NULL)
            fprintf(stderr, "Erreur dans la copie...\n");

        /*
         *  Fill a new char ** with every case between splitted_command[0] and
         *  splitted_command[1].
         */
        i = 1;
        if ((*reworked_command = strcpy(malloc(((strlen(*(splitted_command)) + 1) * sizeof(char))), *(splitted_command))) == NULL)
            fprintf(stderr, "Erreur dans la copie...\n");

        for (; i < max_length - 1; i++)
        {
            char first_character = *(*(reworked_command + i - 1));
            char second_character = *(*(reworked_command + i - 1) + 1);
            char *tmp = malloc(3 * sizeof(char));

            if (first_character > *last)
                *tmp = first_character - 1;
            else if (first_character < *last)
                *tmp = first_character + 1;
            else
                *tmp = first_character;

            if (second_character > *(last + 1))
                *(tmp + 1) = second_character - 1;
            else if (second_character < *(last + 1))
                *(tmp + 1) = second_character + 1;
            else
                *(tmp + 1) = second_character;
            
            *(tmp + 2) = '\0';
            *(reworked_command + i) = tmp;
        }
        *(reworked_command + i) = last;

        /*
         *  Fill the end of the new char ** with every destination of every case
         */
        j = 0;
        x = *(*(splitted_command + 2)) - **reworked_command;
        y = *(*(splitted_command + 2) + 1) - *((*reworked_command) + 1);
        i++;
        for (; i < 2 * max_length; i++)
        {
            char *tmp = malloc(3 * sizeof(char));
            *tmp = *(*(reworked_command + j)) + x;
            *(tmp + 1) = *(*(reworked_command + j) + 1) + y;
            *(tmp + 2) = '\0';

            *(reworked_command + i) = tmp;
            j++;
        }

        i = 0;
        for(; i < command_length; i++)
            free(*(splitted_command + i));
        free(splitted_command); splitted_command = NULL;

        n_command->squares = reworked_command;
        n_command->length = 2*max_length;
        return n_command;
    }
}

void display_error_message(int err_num)
{
    switch(err_num)
    {
        case NOT_POSSIBLE_NO_PLAYER_MARBLE:
            fprintf(stderr, "Pas de pion présent sur l'une des cases séléctionnées...\n");
            break;
        case NOT_POSSIBLE_SQUARES_IDENTICAL:
            fprintf(stderr, "Les cases séléctionnées sont identiques...\n");
            break;
        case NOT_POSSIBLE_SQUARES_NON_ADJACENT:
            fprintf(stderr, "Les cases séléctionnées ne sont pas adjacentes...\n");
            break;
        case NOT_POSSIBLE_SQUARES_NON_ALIGNED:
            fprintf(stderr, "Les cases séléctionnées ne sont pas alignées...\n");
            break;
        case NOT_POSSIBLE_ARRIVAL_SQUARE_NOT_EMPTY:
            fprintf(stderr, "L'une des cases d'arrivées n'est pas vide...\n");
            break;
        case NOT_POSSIBLE_TOO_MUCH_RIVAL_MARBLES:
        case NOT_POSSIBLE_EGAL_PLAYER_AND_RIVAL_MARBLES:
        case NOT_POSSIBLE_MORE_RIVAL_MARBLES_THAN_PLAYER:
            fprintf(stderr, "Vous n'avez pas assez de pions pour effectuer le mouvement (il vous en faut plus que l'adversaire)...\n");
            break;
        case NOT_POSSIBLE_TOO_MUCH_PLAYER_MARBLES:
            fprintf(stderr, "Déplacement trop important de billes...\n");
            break;
        case NOT_POSSIBLE_PLAYER_MARBLE_EJECTION:
            fprintf(stderr, "Ejection d'une de vos bille...\n");
            break;
        default:
            fprintf(stderr, "Erreur...\n");
            break;
    }
}

void free_p_move(p_move *move)
{
   int i = 0;
   for (; i < move->length; i++)
       free( *(move->squares + i) );
   free(move->squares);
   free(move);
}

int game_state(board *b)
{
    fprintf(stdout, "b %d - n %d\n", b->ejected_marble_B, b->ejected_marble_N);
    if (b->ejected_marble_N >= 6)
        return 1;
    if (b->ejected_marble_B >= 6)
        return -1;
    return 0;
}

void end_game(char **command)
{
    free(*command);     *command = NULL;
}

int play_game(int b_player_statut, int n_player_statut, int test_mode, int load_game)
{
    /*  Test mode will be included after... */
    board   game_board;
    char    *command = malloc((CMD_MAX_SIZE + 1) * sizeof(char));
    char    flush;
    int     coup = 1;

    if (load_game)
    {
        /*  Load the game_board and every game information here ... */
    }
    else
    {
        game_board = create_new_board();
    }

    display_board(&game_board);
    while( 1 )
    {
        player current_player = (coup & 1 ? 'B' : 'N');

        if ( (current_player == 'B' && (b_player_statut & H_PLAYER)) ||
             (current_player == 'N' && (n_player_statut & H_PLAYER)) )
        {
            if (!test_mode)
            {
                char *prompt = (current_player == 'B' ? PROMPT_B : PROMPT_N);
                fprintf(stdout, "#%d %s", coup, prompt);
            }
            
            if (fscanf(stdin, "%50s", command) == EOF && test_mode)
                return 1;
            
            if (!test_mode)
                while ((flush = getchar()) != '\n' && flush != EOF);
            else
                fprintf(stdout, "#%d %s\n", coup, command);
        
            if (str_cmp(command, "exit"))
            {   
                end_game(&command);
                return 1;
            }
            else if (0);
            else if (!command_validation(command))
            {
                fprintf(stderr, "WRONG COMMAND, PLAY AGAIN\n");
                continue;
            }
            else
            {
                int m_return;
                p_move *new_command = rework_move(command);
                new_command->color = current_player;
           
                m_return = move_is_possible(&game_board, new_command);
                if (m_return > 0)
                {
                    do_move(&game_board, new_command);
                }
                else
                {
                    if (!test_mode)
                    {
                        fprintf(stderr, "Coup impossible...\n");
                        display_error_message(m_return);
                        continue;
                    }
                    else
                    {
                        display_error_message(m_return);
                        fprintf(stderr, "TEST MODE WILL EXIT...\n");
                        return 1;
                    }
                }
            
                free_p_move(new_command); new_command = NULL;
            }
        }
        else
        {
            p_move *ai_move;
            if ( (current_player == 'B' && (b_player_statut & EASY_AI)) ||
                 (current_player == 'N' && (n_player_statut & EASY_AI)) )
            {
                ai_move = random_move(&game_board, current_player);
            }
            if ( (current_player == 'B' && (b_player_statut & MEDIUM_AI)) ||
                 (current_player == 'N' && (n_player_statut & MEDIUM_AI)) )
            {
                ai_move = heuristic_move(&game_board, current_player);
                fprintf(stdout, "faire jouer l'ia MEDIUM ici... *visible par la variable current_player*\n");
            }
            
            fprintf(stdout, "#%d IA played\n", coup);
            do_move(&game_board, ai_move);
  /*              free_p_move(ai_move); ai_move = NULL; */
        }


        /*
         *  Effectuer les mouvements.
         *  Changer les états de certaines variables (notamment au niveau des
         *  jetons sortis).
         *  Vérifier si il y a un gagnant.
         */
        display_board(&game_board);
        
        int state = game_state(&game_board);
        if (state < 0)
        {
            fprintf(stdout, "NOIR WIN\n");
            return 1;
        }
        if (state > 0)
        {
            fprintf(stdout, "BLANC WIN\n");
            return 1;
        }
        

        coup++;
    }
   
    free(command); command = NULL;

    return 0;
}

