#include "main.h"

int BIN_FOLDER = 1;

int parse_arguments(int argc, char **argv, int *player_b, int *player_n, int *test_mode, int *load_game, char **filename)
{
    int position = 0;
    for (position = 1; position < argc; position++)
    {
        if (str_cmp(*(argv + position), "-B") || str_cmp(*(argv + position), "-N"))
        {
            char c = *(*(argv + position)+1);       
            position++;

            if (position >= argc)
            {
                fprintf(stderr, "Bad argument after -%c...\n", c);
                return 0;
            }
            else if (str_cmp(*(argv + position), "robot"))
            {
                if (c == 'B')
                    *player_b = VERY_EASY_AI;
                else
                    *player_n = VERY_EASY_AI;
            }
            else if (str_cmp(*(argv + position), "robot2"))
            {
                if (c == 'B')
                    *player_b = EASY_AI;
                else
                    *player_n = EASY_AI;
            }
            else if (str_cmp(*(argv + position), "humain"))
            {
                if (c == 'B')
                    *player_b = H_PLAYER;
                else
                    *player_n = H_PLAYER;
            }
            else
            {
                fprintf(stderr, "Bad argument after -%c...\n", c);
                return 0;
            }
        }
        else if (str_cmp(*(argv + position), "-t"))
            *test_mode = 1;
        else if (str_cmp(*(argv + position), "-c"))
        {
            position++;
            if (position >= argc)
            {
                fprintf(stderr, "Bad argument after -c...\n");
                return 0;
            }
            *load_game = 1;
            if ((*filename = strcpy(malloc((strlen(*(argv + position)) + 1) * sizeof(char)), *(argv + position))) == NULL)
                fprintf(stderr, "Erreur dans la copie...\n");
        }
        else
            fprintf(stderr, "Unknown argument : %s\n", *(argv + position));
    }
    return 1;
}

int main(int argc, char **argv)
{
    int player_b = H_PLAYER, player_n = H_PLAYER, test_mode = 0, load_game = 0;
    char *filename;

    if (strncmp(*argv, "./bin", 5) == 0)
        BIN_FOLDER = 0;

    srand(time(NULL));
    
    parse_arguments(argc, argv, &player_b, &player_n, &test_mode, &load_game, &filename);

    play_game(player_b, player_n, test_mode, load_game, filename);
    return EXIT_SUCCESS;
}

