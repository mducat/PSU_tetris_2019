/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** game methods
*/

#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include "tetris.h"

char **init_map(conf_t *conf)
{
    char **map = malloc(sizeof(char *) * (conf->height + 1));

    if (!map)
        return (0);
    map[conf->height] = 0;
    for (int i = 0; i < conf->height; i++){
        map[i] = malloc(sizeof(char) * (conf->width * 2 + 2));
        if (!map[i])
            return (0);
        for (int j = 0; j < conf->width * 2 + 1; j++)
            map[i][j] = 0;
    }
    return (map);
}

game_t *init_game(conf_t *conf)
{
    game_t *game = malloc(sizeof(game_t));
    char **map = init_map(conf);

    if (!game || !map)
        return (0);
    srand((int) ((long) conf & 0xFFFFFFFF));
    game->score = 0;
    game->pause = 0;
    game->high_score = get_high_score();
    game->lines = 0;
    game->level = conf->level_start;
    game->clock = clock();
    game->current = 0;
    game->next = 0;
    game->map = map;
    game->next = pick_piece(conf);
    game->current = 0;
    init_piece(game, conf);
    return (game);
}

void free_game(game_t *game)
{
    save_high_score(game->high_score);
    for (int i = 0; game->map[i] != 0; i++)
        free(game->map[i]);
    free(game->map);
    free(game);
}

int input(game_t *game, conf_t *conf)
{
    int mem = 0;

    game->timeout = clock();
    timeout(0);
    while (clock() - game->timeout < CLOCKS_PER_SEC
        * get_speed(game->level) / 60){
        usleep(10000);
        game->clock -= CLOCKS_PER_SEC / 100;
        game->timeout -= CLOCKS_PER_SEC / 100;
        if ((mem = act(game, conf, getch())) == 1)
            return (1);
        if (mem < 0)
            continue;
        if (is_colliding(game, game->current, conf)){
            lost();
            return (1);
        }
        draw(game, conf);
    }
    return (0);
}

void start_game(conf_t *conf)
{
    game_t *game = init_game(conf);

    initscr();
    start_color();
    for (int i = 0; conf->tetriminos[i] != 0; i++)
        init_pair(conf->tetriminos[i]->color,
            conf->tetriminos[i]->color, COLOR_BLACK);
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    while (1){
        draw(game, conf);
        if (input(game, conf))
            break;
        if (step(game, conf))
            break;
    }
    free_game(game);
    endwin();
}
