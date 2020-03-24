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
        return (1);
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
    conf_t *conf = parse_arguments(ac, av);

    if (!conf)
        return (84);
    if (conf->help){
        my_printf(USAGE, av[0]);
        free(conf);
        return (0);
    }
    if (get_tetriminos(&(conf->tetriminos)))
        return (84);
    if (conf->debug)
        print_conf(conf);
    start_game(conf);
    free(conf);
    return (0);
}
