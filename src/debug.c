/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** debug mode
*/

#include "tetris.h"
#include "my.h"

void print_conf(conf_t *conf)
{
    my_printf("*** DEBUG MODE ***\n");
}

void print_array(char **array)
{
    for (int i = 0; array[i]; i++) {
        my_printf("%s\n", array[i]);
    }
}

void print_tetriminos(tetrimino_t **tetris)
{
    int count = 0;

    for (; tetris[count]; count++);
    my_printf("Tetriminos : %d\n", count);
    for (int i = 0; tetris[i]; i++) {
        my_printf("Tetriminos : Name %s", tetris[i]->name);
        if (tetris[i]->error == 1) {
            my_printf(" : Error\n");
            continue;
        }
        my_printf(" : Size %d*%d", tetris[i]->width, tetris[i]->height);
        my_printf(" : Color %d :\n", tetris[i]->color);
        print_array(tetris[i]->blocks);
    }
}