#include "main.h"

int BIN_FOLDER = 1;

int parse_arguments(int argc, char **argv, int *player_b, int *player_n, int *test_mode, int *load_game, char **filename)
{
    int position;
    int player_option = 0;
    for (position = 1; position < argc; position++)
    {
        if (str_cmp(*(argv + position), "-B") || str_cmp(*(argv + position), "-N"))
        {
            char c = *(*(argv + position)+1);       
            position++;

            if (position >= argc)
            {
                fprintf(stderr, "Mauvais argument après l'argument -%c...\n", c);
                return 0;
            }
            else if (*test_mode)
            {
                fprintf(stderr, "Les arguments `-B|-N` sont incompatibles avec l'argument `-t`...\n)");
                return 0;
            }
            else if (str_cmp(*(argv + position), "ai"))
            {
                if (c == 'B')
                    *player_b = VERY_EASY_AI;
                else
                    *player_n = VERY_EASY_AI;
                player_option = 1;
            }
            else if (str_cmp(*(argv + position), "human"))
            {
                if (c == 'B')
                    *player_b = H_PLAYER;
                else
                    *player_n = H_PLAYER;
                player_option = 1;
            }
            else
            {
                fprintf(stderr, "Mauvais argument après l'argument -%c...\n", c);
                return 0;
            }
        }
        else if (str_cmp(*(argv + position), "-t"))
        {
            if (player_option)
            {
                fprintf(stderr, "Les arguments `-B|-N` sont incompatibles avec l'argument `-t`...\n)");
                return 0;
            }
            *test_mode = 1;
        }
        else if (str_cmp(*(argv + position), "-c"))
        {
            position++;
            if (position >= argc)
            {
                fprintf(stderr, "Mauvais argument après l'argument -c...\n");
                return 0;
            }
            *load_game = 1;
            if ((*filename = strcpy(malloc((strlen(*(argv + position)) + 1) * sizeof(char)), *(argv + position))) == NULL)
                fprintf(stderr, "Erreur dans la copie...\n");
        }
        else
            fprintf(stderr, "Argument inconnu : %s\n", *(argv + position));
    }
    return 1;
}

int main(int argc, char **argv)
{
    char *filename;
    int player_b = H_PLAYER, player_n = H_PLAYER, test_mode = 0, load_game = 0;

    if (strncmp(*argv, "./bin", 5) == 0)
        BIN_FOLDER = 0;

    srand(time(NULL));
    
    if ( !parse_arguments(  argc, argv, &player_b, &player_n, 
                            &test_mode, &load_game, &filename) )
    {
        return EXIT_FAILURE;
    }

    play_game(player_b, player_n, test_mode, load_game, filename);
    return EXIT_SUCCESS;
}

