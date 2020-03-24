/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** draw UI
*/

#include <ncurses.h>

#include "tetris.h"

void draw_border(int x, int y, int width, int height)
{
    for (int i = 1; i < height; i++){
        mvprintw(y + i, x, "|");
        mvprintw(y + i, x + width, "|");
    }
    for (int i = 1; i < width; i++){
        mvprintw(y, x + i, "-");
        mvprintw(y + height, x + i, "-");
    }
    mvprintw(y, x, "+");
    mvprintw(y + height, x, "+");
    mvprintw(y, x + width, "+");
    mvprintw(y + height, x + width, "+");
}

void draw_map(int x, int y, char **map)
{
    for (int i = 0; map[i] != 0; i++)
        mvprintw(y + i, x, map[i]);
}

void display(game_t *game, conf_t *conf)
{
    draw_border(20, 10, conf->width, conf->height);
    draw_map(20, 10, game->map);
}
