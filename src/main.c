/*
** EPITECH PROJECT, 2019
** tetris
** File description:
** main
*/

#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>

#include "tetris.h"
#include "my.h"

int get_tetriminos(tetrimino_t ***list)
{
    char **files = get_tetriminos_file();
    tetrimino_t **tetriminos;
    int tetri_c = 0;

    if (files == NULL)
        return (0);
    for (; files[tetri_c]; tetri_c++);
    tetriminos = malloc(sizeof(tetrimino_t *) * (tetri_c + 1));
    for (int i = 0; files[i]; i++)
        tetriminos[i] = get_tetrimino_from_file(files[i]);
    tetriminos[tetri_c] = NULL;
    sort_tetriminos(tetriminos);
    *list = tetriminos;
    return (0);
}

int main(int ac, char **av)
{
    int status = 0;
    conf_t *conf = parse_arguments(ac, av);
    tetrimino_t **tetriminos;

    if (!conf)
        return (84);
    status = get_tetriminos(&tetriminos);
    if (status)
        return (84);
    if (conf->debug) {
        print_conf(conf);
        print_tetriminos(tetriminos);
    }

    free(conf);
    return (0);
}
