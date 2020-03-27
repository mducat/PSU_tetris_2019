/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** tetriminos rotation
*/

#include <stdlib.h>

#include "tetris.h"

char **malloc_array(char **from, current_t *cur)
{
    char **blocks = 0;
    int tmp;

    blocks = malloc(sizeof(char *) * (cur->width + 1));
    blocks[cur->width] = 0;
    if (!blocks)
        exit(84);
    for (int i = 0; i < cur->width; i++){
        blocks[i] = malloc(sizeof(char) * (cur->height + 1));
        if (!blocks[i])
            exit(84);
        for (int j = 0; j < cur->height; j++)
            blocks[i][j] = ' ';
        blocks[i][cur->height] = 0;
    }
    tmp = cur->width;
    cur->width = cur->height;
    cur->height = tmp;
    return (blocks);
}

char **rotate_clockwise(char **from, current_t *cur)
{
    int width = cur->width;
    char **blocks = malloc_array(from, cur);
    int new_col = 0;
    int new_row = 0;
    int old_col = 0;
    int old_row = 0;

    for (; from[old_col] != 0; old_col++);
    for (old_col--; old_col >= 0; old_col--, new_row++){
        new_col = 0;
        for (old_row = 0; old_row < width; old_row++, new_col++)
            blocks[old_row][old_col] = from[new_row][new_col];
    }
    return (blocks);
}

void rotate_blocks(current_t *current, game_t *game, conf_t *conf)
{
    char **old_blocks = current->blocks;
    char **new_blocks = rotate_clockwise(old_blocks, current);
    int tmp = 0;

    current->blocks = new_blocks;
    if (is_colliding(game, current, conf)){
        current->blocks = old_blocks;
        for (int i = 0; new_blocks[i] != 0; i++)
            free(new_blocks[i]);
        free(new_blocks);
        tmp = current->width;
        current->width = current->height;
        current->height = tmp;
        return;
    }
    for (int i = 0; old_blocks[i] != 0; i++)
        free(old_blocks[i]);
    free(old_blocks);
}
