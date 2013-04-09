#ifndef H_GAME
#define H_GAME

#include <regex.h>

#include "utility.h"
#include "board.h"

#define PROMPT_B "Joueur Blanc > "
#define PROMPT_N "Joueur Noir  > "

#define DONT_MATCH 0
#define MATCH 1

#define CMD_MAX_SIZE 100

int play_game(int, int, int, int);
int command_validation(const char *);
char **split_command(char *, int *);
char **rework_move(char *, int *);

#endif

