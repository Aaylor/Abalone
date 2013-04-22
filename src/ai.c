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

p_move *heuristic_move(board *b, player cur_player)
{
    int i, j, ai_p_move_length = 0;
    int count_marble_ejection = 0, count_push_opponent_marble = 0;
    p_move *h_move, *ai_possible_movement;
    p_move **marble_ejection = NULL, **push_opponent_marble = NULL;

    h_move = malloc(sizeof(p_move));
    ai_possible_movement = possible_movements(b, cur_player, &ai_p_move_length);
    
    for (i = 0; i < ai_p_move_length; i++)
    {
        /*
        fprintf(stdout, "COUP : ");
        for(j = 0; j < (ai_possible_movement + i)->length; j++)
        {
            fprintf(stdout, "%s ", *((ai_possible_movement + i)->squares + j));
        }
        putchar('\n');
        */
        if (does_move_eject_marble(b, (ai_possible_movement + i)))
        {
            fprintf(stdout, "HERE I AM\n");
            if (count_marble_ejection)
            {
                p_move **tmp = realloc(marble_ejection, (sizeof(p_move *) * ((count_marble_ejection++) + 1)));
                if (tmp)
                    marble_ejection = tmp;
                else
                    free(tmp);
             }
             else
             {
                marble_ejection = malloc(sizeof(p_move *));
             }
             *(marble_ejection + count_marble_ejection) = (ai_possible_movement + i);
        }
        else if( 1 )    /* if it move an opponent marble */
        {
            if (count_push_opponent_marble)
            {
                p_move **tmp = realloc( push_opponent_marble,
                                        (sizeof(p_move *) * ((count_push_opponent_marble++) + 1)));
                if (tmp)
                    push_opponent_marble = tmp;
                else
                    free(tmp);
            }
            else
            {
                push_opponent_marble = malloc(sizeof(p_move *));
            }
            *(push_opponent_marble + count_push_opponent_marble) = (ai_possible_movement + i);
        }
    }

    if ( marble_ejection );
        /*  choose according to the barycentre...   */
    else if( push_opponent_marble );
        /*  choose according to the barycentre...   */
    else;
        /*  choose according to the barycentre...   */

    return h_move;
}

