#ifndef H_GAME
#define H_GAME

#include <unistd.h>
#include <regex.h>

#include "utility.h"
#include "board.h"
#include "ai.h"

#define PROMPT_B "Joueur Blanc > "
#define PROMPT_N "Joueur Noir  > "

#define DONT_MATCH 0
#define MATCH 1

#define CMD_MAX_SIZE 50

#define change_player(cur) (cur == 'B' ? 'N' : 'B')

/*
 *  Function use to read the save file, to see if there is any problem with it
 *  (incorrect count of marbles, incorrect syntax, ...)
 */
int first_read(const char *);

/*
 *  Function which load the game.
 */
int read_file_to_load_game(board *, player *, const char *);

/*
 *  Function to save the game.
 */
int save_game(char, board *);

/*
 *  Test is the command entered by the user meets the standards of this program.
 *  It must be like : <CHAR><INT>-(<CHAR><INT>-)<CHAR><INT>
 */
int command_validation(const char *);

/*
 *  Give an array with every arguments given by the user command.
 *  It used only with the function `rework_move`
 */
char **split_command(char *, int *);

/*
 *  Give the explicit command
 */
p_move *rework_move(char *);

/*
 *  Display the error message according to the number
 */
void display_error_message(int);

/*
 *  Main function where users can play
 */
int play_game(int, int, int, int, char *);

/*
 *  Entirely free the p_move struct
 */
void free_p_move(p_move *);

/*
 *  Return the state of game (if there is any player who won or not).
 */
int game_state(board *);

/*
 *  Function use to end the game.
 *  It frees the command variable and the board
 */
void end_game(char **);

#endif

