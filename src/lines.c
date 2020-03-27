/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** lines handling
*/

#include <stdlib.h>

#include "tetris.h"

void delete_line(game_t *game, conf_t *conf, int i)
{
    free(game->map[i]);
    for (int j = 0; j < i; j++){
        game->map[i - j] = game->map[i - j - 1];
    }
    game->map[0] = malloc(sizeof(char) * (conf->width * 2 + 2));
    for (int j = 0; j < conf->width * 2 + 1; j++)
        game->map[0][j] = 0;
}

int check_single_line(game_t *game, conf_t *conf, int i)
{
    for (int j = 0; j < conf->width - 1; j++){
        if (game->map[i][j * 2] != '*')
            return (0);
    }
    delete_line(game, conf, i);
    game->lines += 1;
    game->level = conf->level_start + game->lines / 10;
    return (1);
}

int get_mult(int counter)
{
    switch (counter){
    case 0: return (0);
    case 1: return (50);
    case 2: return (150);
    case 3: return (350);
    }
    return (1000);
}

void check_lines(game_t *game, conf_t *conf)
{
    int counter = 0;
    int mult = 0;

    for (int i = 0; game->map[i] != 0; i++){
        if (check_single_line(game, conf, i)){
            i = 0;
            counter++;
        }
    }
    if (!counter || !is_map_empty(game->map, conf->width))
        game->score += get_mult(counter) * (game->level + 1);
    else
        game->score += 2000 * (game->level + 1);
    if (game->score > game->high_score)
        game->high_score = game->score;
}
