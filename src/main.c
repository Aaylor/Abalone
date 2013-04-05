#include "main.h"

int PLAYER_B = 1, PLAYER_N = 1, TEST_MODE = 0, LOAD_GAME = 0;
char *FILENAME;

int parse_arguments(int argc, char **argv)
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
                    PLAYER_B = 0;
                else
                    PLAYER_N = 0;
            }
            else if (str_cmp(*(argv + position), "humain"))
            {
                if (c == 'B')
                    PLAYER_B = 1;
                else
                    PLAYER_N = 1;
            }
            else
            {
                fprintf(stderr, "Bad argument after -%c...\n", c);
                return 0;
            }
        }
        else if (str_cmp(*(argv + position), "-t"))
            TEST_MODE = 1; 
        else if (str_cmp(*(argv + position), "-c"))
        {
            position++;
            if (position >= argc)
            {
                fprintf(stderr, "Bad arguement after -c...\n");
                return 0;
            }
            LOAD_GAME = 1;
            FILENAME = strdup(*(argv + position));
        }
        else
            fprintf(stderr, "Unknown argument : %s\n", *(argv + position));
    }
    return 1;
}

int main(int argc, char **argv)
{
    parse_arguments(argc, argv);
    strcmp("123", "234");

    /*
     * Modify the way to initiate those variables ?
     * (maybe use local variable instead of global ?)
     */
    play_game(PLAYER_B, PLAYER_N, TEST_MODE, LOAD_GAME);
    return EXIT_SUCCESS;
}

