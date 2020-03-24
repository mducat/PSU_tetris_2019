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

void act(game_t *game, conf_t *conf, int c)
{
    if (c == conf->key_right)
        mvprintw(0, 0, "Right !");
    if (c == conf->key_left)
        mvprintw(0, 0, "Left !");
    if (c == conf->key_drop)
        mvprintw(0, 0, "Drop !");
    if (c == conf->key_quit)
        mvprintw(0, 0, "Quit !");
    if (c == conf->key_turn)
        mvprintw(0, 0, "Turn !");
    if (c == conf->key_pause)
        mvprintw(0, 0, "Pause !");
}

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
        for (int j = 0; j < conf->width * 2 + 1; j ++)
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
    game->score = 0;
    game->high_score = 0;
    game->lines = 0;
    game->level = conf->level_start;
    game->clock = clock();
    game->current = 0;
    game->next = 0;
    game->map = map;
    return (game);
}

void free_game(game_t *game)
{
    for (int i = 0; game->map[i] != 0; i++)
        free(game->map[i]);
    free(game->map);
    free(game);
}

void game_loop(conf_t *conf, game_t *game)
{
    int c;
    int buf;

    while (1){
        clear();
        while ((buf = getch()) > 0)
            c = buf;
        act(game, conf, c);
        display(game, conf);
        c = -1;
        refresh();
        usleep(1000000);
    }
}

void start_game(conf_t *conf)
{
    game_t *game = init_game(conf);

    initscr();
    keypad(stdscr, TRUE);
    noecho();
    timeout(0);
    curs_set(0);
    game_loop(conf, game);
    free_game(game);
    endwin();
}
