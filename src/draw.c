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

void draw_map(int x, int y, char **map, conf_t *conf)
{
    for (int i = 0; map[i] != 0; i++){
        for (int j = 0; j < conf->width * 2; j++){
            if (map[i][j] < 16)
                continue;
            attron(COLOR_PAIR(map[i][j + 1]));
            attron(A_BOLD);
            mvprintw(y + i + 1, x + j + 1, "%c", map[i][j]);
            attroff(COLOR_PAIR(map[i][j + 1]));
            attroff(A_BOLD);
        }
    }
}

void draw_current(int x, int y, game_t *game)
{
    for (int i = 0; game->current->blocks[i] != 0; i++){
        attron(COLOR_PAIR(game->current->piece->color));
        attron(A_BOLD);
        for (int j = 0; game->current->blocks[i][j] != 0; j++)
            mvprintw(y + game->current->cur_y + i + 1,
                x + (game->current->cur_x + j) * 2 + 1,
                "%c", game->current->blocks[i][j]);
        attroff(COLOR_PAIR(game->current->piece->color));
        attroff(A_BOLD);
    }
}

void display(game_t *game, conf_t *conf)
{
    int x = 20;
    int y = 10;

    draw_current(x, y, game);
    my_printf("\033[0m");
    refresh();
    draw_border(x, y, conf->width * 2 - 2, conf->height);
    draw_map(x, y, game->map, conf);
    if (!conf->without_next){
        draw_border(x + conf->width * 2 + 10, y, 8, 8);
        for (int i = 0; game->next->blocks[i] != 0; i++)
            mvprintw(1 + y + i, x + conf->width * 2 + 11,
                game->next->blocks[i]);
    }
}
