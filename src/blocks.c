/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** blocks manipulation
*/

#include <stdlib.h>
#include <ncurses.h>

#include "my.h"
#include "tetris.h"

char **array_dup(char **array, int width)
{
    char **dup = 0;
    int size = 0;

    for (; array[size] != NULL; size++);
    dup = malloc(sizeof(char *) * (size + 1));
    if (!dup)
        return (0);
    dup[size] = NULL;
    for (int i = 0; array[i] != NULL; i++){
        dup[i] = malloc(width + 1);
        if (!dup[i])
            return (0);
        for (int j = 0; j < width + 1; j++)
            dup[i][j] = 0;
        for (int j = 0; array[i][j] != 0; j++)
            dup[i][j] = array[i][j];
    }
    return (dup);
}

int is_line_empty(char *map, int width)
{
    for (int i = 0; i < width; i++)
        if (map[i * 2] == '*')
            return (0);
    return (1);
}

int is_map_empty(char **map, int width)
{
    for (int i = 0; map[i] != 0; i++){
        if (!is_line_empty(map[i], width))
            return (0);
    }
    return (1);
}

void draw(game_t *game, conf_t *conf)
{
    int x;
    int y;

    clear();
    getmaxyx(stdscr, y, x);
    if (x < 51 + 2 * conf->width + game->current->width
        || y < 2 + max(conf->height, game->current->height))
        mvprintw(y / 2 - 1, (x - 29) / 2, "Please enlarge the terminal !");
    else
        display(game, conf);
    refresh();
}
