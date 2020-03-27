/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** draw UI
*/

#include <ncurses.h>
#include <time.h>

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
        for (int j = 0; j < game->current->width; j++)
            mvprintw(y + game->current->cur_y + i + 1,
                x + (game->current->cur_x + j) * 2 + 1,
                "%c", game->current->blocks[i][j]);
        attroff(COLOR_PAIR(game->current->piece->color));
        attroff(A_BOLD);
    }
}

void draw_data(int x, int y, game_t *game, conf_t *conf)
{
    int data_w = 30;
    int data_padding = 1;
    clock_t diff = clock() - game->clock;

    attron(A_BOLD);
    mvprintw(y + 1, x, " High score%*d", data_w - 13, game->high_score);
    mvprintw(y + 2, x, " Score%*d", data_w - 8, game->score);
    mvprintw(y + 4, x, " Lines%*d", data_w - 8, game->lines);
    mvprintw(y + 5, x, " Level%*d", data_w - 8, game->level);
    mvprintw(y + 7, x, " Timer%*s%02d:%02d", data_w - 13, "",
        (diff / (60 * CLOCKS_PER_SEC)) % 60, (diff / CLOCKS_PER_SEC) % 60);
    attroff(A_BOLD);
}

void display(game_t *game, conf_t *conf)
{
    int x = 10;
    int y = 10;
    int data_w = 30;
    int margin = 4;

    draw_border(x, y, data_w, 10);
    draw_data(x + 1, y + 1, game, conf);
    draw_current(x + data_w + margin, y, game);
    draw_border(x + data_w + margin, y, conf->width * 2 - 2, conf->height);
    draw_map(x + data_w + margin, y, game->map, conf);
    if (!conf->without_next){
        draw_border(x + data_w + margin + conf->width * 2 + 10, y, 8, 8);
        for (int i = 0; game->next->blocks[i] != 0; i++)
            mvprintw(1 + y + i, x + conf->width * 2 + 11 + data_w + margin,
                game->next->blocks[i]);
    }
}
