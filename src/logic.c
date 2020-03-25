/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** game logic
*/

#include <stdlib.h>
#include <ncurses.h>

#include "tetris.h"

void init_piece(game_t *game, conf_t *conf)
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
    game->current->cur_x = 0;
    game->current->blocks = array_dup(game->next->blocks);
    game->next = pick_piece(conf);
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

void step(game_t *game, conf_t *conf)
{
    game->current->cur_y += 1;
    if (is_colliding(game, game->current, conf)){
        game->current->cur_y -= 1;
        merge_map(game, game->current);
        init_piece(game, conf);
    }
}

int act(game_t *game, conf_t *conf, int c)
{
    int old_x = game->current->cur_x;

    if (c < 0)
        return (-1);
    if (c == conf->key_right)
        game->current->cur_x += 1;
    if (c == conf->key_left)
        game->current->cur_x -= 1;
    if (c == conf->key_drop)
        step(game, conf);
    if (c == conf->key_quit)
        return (1);
    if (c == conf->key_turn)
        mvprintw(0, 0, "Turn !");
    if (c == conf->key_pause)
        mvprintw(0, 0, "Pause !");
    if (game->current->cur_x < 0 || game->current->cur_x > conf->width - 1 -
        game->current->piece->width || is_colliding(game, game->current, conf))
        game->current->cur_x = old_x;
    return (0);
}
