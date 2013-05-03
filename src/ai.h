#ifndef H_AI
#define H_AI

#include "board.h"
#include "game.h"
#include "utility.h"

void    free_array(p_move *, int, p_move *);
p_move  *random_move(board *, player);
int get_ponderation_value(p_move *);
p_move  *easy_ai(board *, player);

#endif

