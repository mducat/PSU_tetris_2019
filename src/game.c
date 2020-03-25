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
        map[i] = malloc(sizeof(char) * (conf->width * 2 + 1));
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
    game->high_score = 0;
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
    for (int i = 0; game->map[i] != 0; i++)
        free(game->map[i]);
    free(game->map);
    free(game);
}

int input(game_t *game, conf_t *conf)
{
    int mem = 0;

    game->timeout = clock();
    timeout(10);
    while (clock() - game->timeout < 10000){
        if ((mem = act(game, conf, getch())) == 1)
            return (1);
        if (mem < 0)
            continue;
        clear();
        display(game, conf);
        refresh();
    }
    return (0);
}

void start_game(conf_t *conf)
{
    game_t *game = init_game(conf);

    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    while (1){
        clear();
        display(game, conf);
        refresh();
        if (input(game, conf))
            break;
        step(game, conf);
    }
    free_game(game);
    endwin();
}
