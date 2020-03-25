/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** map handling
*/

#include "tetris.h"

int is_line_colliding(game_t *game, current_t *current, conf_t *conf, int i)
{
    for (int j = 0; current->blocks[i][j] != 0; j++){
        if (current->blocks[i][j] != '*')
            continue;
        if (game->map[current->cur_y + i][(current->cur_x + j) * 2] == '*')
            return (1);
    }
    return (0);
}

int is_colliding(game_t *game, current_t *current, conf_t *conf)
{
    if (current->cur_y + current->piece->height + 1 > conf->height)
        return (1);
    for (int i = 0; current->blocks[i] != 0; i++)
        if (is_line_colliding(game, current, conf, i))
            return (1);
    return (0);
}

void merge_line(game_t *game, current_t *current, int i)
{
    for (int j = 0; current->blocks[i][j] != 0; j++){
        if (current->blocks[i][j] != '*')
            continue;
        game->map[current->cur_y + i][(current->cur_x + j) * 2] = '*';
        game->map[current->cur_y + i][(current->cur_x + j) * 2 + 1] =
            current->piece->color;
    }
}

void merge_map(game_t *game, current_t *current)
{
    for (int i = 0; current->blocks[i] != 0; i++)
        merge_line(game, current, i);
}
