#include "ai.h"

static int ponderation_array[BOARD_LENGTH][BOARD_LENGTH] = \
{{0, 0, 0, 1, 6, 6, 6, 6, 1 },    
 {0, 0, 0, 1, 6, 6, 6, 6, 1 },
 {0, 0, 1, 6, 7, 7, 7, 6, 1 }, 
 {0, 1, 6, 7, 8, 8, 7, 6, 1 },
 {1, 6, 7, 8, 9, 8, 7, 6, 1 },
 {1, 6, 7, 8, 8, 7, 6, 1, 0 },
 {1, 6, 7, 7, 7, 6, 1, 0, 0 },
 {1, 6, 6, 6, 6, 1, 0, 0, 0 },
 {1, 1, 1, 1, 1, 0, 0, 0, 0 }};

void free_array(p_move *array_to_free, int array_length, p_move *ptr_to_save)
{
    int i, j;
    for(i = 0; i < array_length; i++)
    {
        if ((array_to_free + i) != ptr_to_save)
        {
            for(j = 0; j < (array_to_free + i)->length; j++)
                free(*((array_to_free + i)->squares + j));
            free((array_to_free + i)->squares);
        }
    }
    free(array_to_free);
}

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

int get_ponderation_value(p_move *cur_move)
{
    int i, result = 1;
    for (i = cur_move->length/2; i < cur_move->length; i++)
    {
        result *= ponderation_array[c_to_key((cur_move->squares)[i][0])][((cur_move->squares)[i][1]) - '1'];
    }

    return result;
}

p_move *heuristic_move(board *b, player cur_player)
{
    int i, j, ai_p_move_length = 0;
    int count_marble_ejection = 0, count_push_opponent_marble = 0;
    p_move *h_move, *ai_possible_movement;
    p_move **marble_ejection = NULL, **push_opponent_marble = NULL;

    h_move = malloc(sizeof(p_move));
    ai_possible_movement = possible_movements(b, cur_player, &ai_p_move_length);
    
    fprintf(stdout, "length : %d\n", ai_p_move_length);

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
        if (what_marble_does_move_ejects(b, (ai_possible_movement + i)))
        {
            fprintf(stdout, "HERE I AM\n");
            if (count_marble_ejection)
            {
                p_move **tmp = realloc(marble_ejection, (sizeof(p_move *) * ((++count_marble_ejection) + 1)));
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
             fprintf(stdout, "%p - %p\n", *(marble_ejection + count_marble_ejection), (ai_possible_movement + i));
        }
        else if(!what_marble_does_move_ejects(b, (ai_possible_movement + i))
                && (b->tab
                    [c_to_key(((ai_possible_movement + i)->squares)[((ai_possible_movement + i)->length/2)][0])] \
                    [((ai_possible_movement + i)->squares)[((ai_possible_movement + i)->length/2)][1] - '1'] != '.'))    /* if it move an opponent marble */
        {
            if (count_push_opponent_marble)
            {
                p_move **tmp = realloc( push_opponent_marble,
                                        (sizeof(p_move *) * ((++count_push_opponent_marble) + 1)));
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

    if ( marble_ejection )
    {
        p_move *tmp = *marble_ejection;
        int max_pond = get_ponderation_value(tmp);
        fprintf(stdout, "\t CUR PONDERATION : %d\n", max_pond);
        for (i = 1; i < count_marble_ejection; i++)
        {
            int cur_pond = get_ponderation_value(*(marble_ejection + i));
            fprintf(stdout, "\t CUR PONDERATION : %d\n", cur_pond);
            if (cur_pond > max_pond)
            {
                max_pond = cur_pond;
                tmp = *(marble_ejection + i);
            }
        }

        h_move->squares = tmp->squares;
        h_move->length = tmp->length;
        h_move->color = tmp->color;
    }
    else if( push_opponent_marble )
    {
        p_move *tmp = *push_opponent_marble;
        int max_pond = get_ponderation_value(tmp);
        fprintf(stdout, "\t CUR PONDERATION : %d\n", max_pond);
        for (i = 1; i < count_push_opponent_marble; i++)
        {
            int cur_pond = get_ponderation_value(*(push_opponent_marble + i));
            fprintf(stdout, "\t CUR PONDERATION : %d\n", cur_pond);
            if (cur_pond > max_pond)
            {
                max_pond = cur_pond;
                tmp = *(push_opponent_marble + i);
            }
        }

        h_move->squares = tmp->squares;
        h_move->length = tmp->length;
        h_move->color = tmp->color;
    }
    else
    {
        p_move *tmp = ai_possible_movement;
        int max_pond = get_ponderation_value(tmp);
        fprintf(stdout, "\t CUR PONDERATION : %d\n", max_pond);
        for (i = 1; i < ai_p_move_length; i++)
        {
            int cur_pond = get_ponderation_value(tmp + i);
            fprintf(stdout, "\t CUR PONDERATION : %d\n", cur_pond);
            if (cur_pond > max_pond)
            {
                max_pond = cur_pond;
                tmp = ai_possible_movement + i;
            }
        }

        h_move->squares = tmp->squares;
        h_move->length = tmp->length;
        h_move->color = tmp->color;
    }

    return h_move;
}

