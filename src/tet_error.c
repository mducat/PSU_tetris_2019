/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** tetriminos error
*/

#include <stdlib.h>

#include "tetris.h"

void check_char(tetrimino_t *piece, int i, int j)
{
    if (piece->blocks[i][j] != ' '
        && piece->blocks[i][j] != '*'
        && piece->blocks[i][j] != 0)
        piece->error = 1;
}

void check_tet_content(tetrimino_t *piece)
{
    if (piece->error)
        return;
    for (int i = 0; i < piece->height != 0; i++)
        for (int j = 0; j < piece->width; j++)
            check_char(piece, i, j);
}

void chk_conf_game(conf_t *conf)
{
    for (int i = 0; conf->tetriminos[i] != 0; i++)
        if (!conf->tetriminos[i]->error)
            return;
    exit(84);
}
