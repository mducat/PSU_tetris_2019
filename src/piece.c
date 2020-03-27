/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** piece init
*/

#include <stdlib.h>

#include "tetris.h"

int init_piece(game_t *game, conf_t *conf)
{
    int size = 0;
    char **dup;

    if (!game->current)
        game->current = malloc(sizeof(current_t));
    else
        free_array(game->current->blocks);
    if (!game->current)
        exit(84);
    for (; conf->tetriminos[size] != 0; size++);
    game->current->piece = game->next;
    game->current->cur_y = 0;
    game->current->cur_x = (conf->width - game->next->width) / 2;
    game->current->blocks = array_dup(game->next->blocks, game->next->width);
    game->current->width = game->next->width;
    game->current->height = game->next->height;
    game->next = pick_piece(conf);
    if (is_colliding(game, game->current, conf))
        return (1);
    return (0);
}

tetrimino_t *pick_piece(conf_t *conf)
{
    int size = 0;
    tetrimino_t *piece;

    for (; conf->tetriminos[size] != 0; size++);
    if (!size)
        return (0);
    piece = conf->tetriminos[rand() % size];
    while (piece->error)
        piece = conf->tetriminos[rand() % size];
    return (piece);
}
