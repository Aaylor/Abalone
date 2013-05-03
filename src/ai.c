#include "ai.h"

static int ponderation_array[BOARD_LENGTH][BOARD_LENGTH] = \
{{0, 0, 0, 0, 1, 1, 1, 1, 1 },    
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

    p_move  *very_easy_ai_move = malloc(sizeof(p_move));
    p_move  *ai_possible_movement = possible_movements(b, cur_player, &ai_p_move_length);
    int     random_move_num = get_random_num(ai_p_move_length);
   
    very_easy_ai_move->squares   = (ai_possible_movement + random_move_num)->squares;
    very_easy_ai_move->length    = (ai_possible_movement + random_move_num)->length;
    very_easy_ai_move->color     = cur_player;

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
    
    return very_easy_ai_move;
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

int evaluate_move(p_move *move)
{
    return 0;
}

p_move *easy_ai(board *b, player cur_player)
{
    int i, j, ai_p_move_length = 0;
    int count_marble_ejection = 0, count_push_opponent_marble = 0, count_else = 0;
    int *keys_marble_ejection = NULL, *keys_push_opponent_marble = NULL;
    p_move *h_move, *ai_possible_movement;

    h_move = malloc(sizeof(p_move));
    ai_possible_movement = possible_movements(b, cur_player, &ai_p_move_length);
    
    fprintf(stdout, "length : %d\n", ai_p_move_length);
    player opponent = (cur_player == 'B' ? 'N' : 'B');

    for (i = 0; i < ai_p_move_length; i++)
    {
        if (what_marble_does_move_ejects(b, (ai_possible_movement + i)))
        {
            fprintf(stdout, "HERE I AM\n");
            if (count_marble_ejection)
            {
                int *tmp = realloc(keys_marble_ejection, (sizeof(int) * ((++count_marble_ejection) + 1)));
                if (tmp)
                    keys_marble_ejection = tmp;
                else
                    free(tmp);
             }
             else
             {
                keys_marble_ejection = malloc(sizeof(int));
             }
             *(keys_marble_ejection + count_marble_ejection) = i;
        }
        else if(!what_marble_does_move_ejects(b, (ai_possible_movement + i))
                && (b->tab
                    [c_to_key(((ai_possible_movement + i)->squares)[((ai_possible_movement + i)->length/2)][0])] \
                    [((ai_possible_movement + i)->squares)[((ai_possible_movement + i)->length/2)][1] - '1'] == opponent))
        {
            if (count_push_opponent_marble)
            {
                int *tmp = realloc( keys_push_opponent_marble,
                                    (sizeof(int) * ((++count_push_opponent_marble) + 1)));
                if (tmp)
                    keys_push_opponent_marble = tmp;
                else
                    free(tmp);
            }
            else
            {
                keys_push_opponent_marble = malloc(sizeof(int));
            }
            *(keys_push_opponent_marble + count_push_opponent_marble) = i;
        }
    }

    int random_choice;
    if (count_marble_ejection)
        random_choice = get_random_num(count_marble_ejection);
    else if (count_push_opponent_marble)
        random_choice = get_random_num(count_push_opponent_marble);
    else
        random_choice = get_random_num(ai_p_move_length);

    h_move->squares = (ai_possible_movement + random_choice)->squares;
    h_move->length  = (ai_possible_movement + random_choice)->length;
    h_move->color   = (ai_possible_movement + random_choice)->color;

    free(keys_marble_ejection);
    free(keys_push_opponent_marble);

    return h_move;
}


    /*
    if ( marble_ejection )
    {
        p_move *tmp = *marble_ejection;
        int max_pond = get_ponderation_value(tmp);
        for (i = 1; i < count_marble_ejection; i++)
        {
            int cur_pond = get_ponderation_value(*(marble_ejection + i));
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
        for (i = 1; i < count_push_opponent_marble; i++)
        {
            int cur_pond = get_ponderation_value(*(push_opponent_marble + i));
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
        for (i = 1; i < ai_p_move_length; i++)
        {
            int cur_pond = get_ponderation_value(tmp + i);
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
zx*/
