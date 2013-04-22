#include "ai.h"

p_move *random_move(board *b, player cur_player)
{
    int i, j;
    int ai_p_move_length = 0;

    p_move  *easy_ai_move = malloc(sizeof(p_move));
    p_move  *ai_possible_movement = possible_movements(b, cur_player, &ai_p_move_length);
    int     random_move_num = get_random_num(ai_p_move_length);
   
    easy_ai_move->squares   = (ai_possible_movement + random_move_num)->squares;
    easy_ai_move->length    = (ai_possible_movement + random_move_num)->length;
    easy_ai_move->color     = cur_player;

    for(i = 0; i < ai_p_move_length; i++)
    {
        if (i != random_move_num)
        {
            for(j = 0; j < (ai_possible_movement + i)->length; j++)
                free(*((ai_possible_movement + i)->squares + j));
            free((ai_possible_movement + i)->squares);
        }
    }
    free(ai_possible_movement);
    
    return easy_ai_move;
}

