/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** game logic
*/

#include <stdlib.h>
#include <ncurses.h>

#include "tetris.h"

int pause(conf_t *conf, game_t *game)
{
    int ret = 0;
    int c;

    timeout(-1);
    while (c = getch()){
        if (c == conf->key_pause || c == conf->key_quit){
            ret = (c == conf->key_quit ? 1 : 0);
            break;
        }
    }
    timeout(0);
    return (ret);
}

int step(game_t *game, conf_t *conf)
{
    if (game->pause)
        return (0);
    game->current->cur_y += 1;
    if (is_colliding(game, game->current, conf)){
        game->current->cur_y -= 1;
        merge_map(game, game->current);
        if (init_piece(game, conf)){
            lost();
            return (1);
        }
    }
    check_lines(game, conf);
    return (0);
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
        rotate_blocks(game->current, game, conf);
    if (c == conf->key_pause)
        return (pause(conf, game));
    if (game->current->cur_x < 0 || game->current->cur_x > conf->width - 1 -
        game->current->width || is_colliding(game, game->current, conf))
        game->current->cur_x = old_x;
    return (0);
}
