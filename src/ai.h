#ifndef H_AI
#define H_AI

#include "board.h"
#include "game.h"
#include "utility.h"

p_move *random_move(board *, player);
p_move *heuristic_move(board *, player);

#endif

