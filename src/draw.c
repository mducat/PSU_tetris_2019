/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** draw UI
*/

#include <ncurses.h>

#include "tetris.h"
#include "my.h"

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

void draw_current(int x, int y, game_t *game)
{
    for (int i = 0; game->current->blocks[i] != 0; i++){
        my_printf("\033[1;%dm", 31 + game->current->piece->color);
        mvprintw(y + game->current->cur_y + i + 1,
            x + game->current->cur_x + 1,
            game->current->blocks[i]);
        refresh();
    }
}

void display(game_t *game, conf_t *conf)
{
    int x = 20;
    int y = 10;

    draw_current(x, y, game);
    my_printf("\033[0m");
    refresh();
    draw_border(x, y, conf->width, conf->height);
    draw_map(x, y, game->map);
    if (!conf->without_next){
        draw_border(x + conf->width + 10, y, 8, 8);
        for (int i = 0; game->next->blocks[i] != 0; i++)
            mvprintw(1 + y + i, x + conf->width + 11,
                game->next->blocks[i]);
    }
}
