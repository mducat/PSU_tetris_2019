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

void check_tetriminos(conf_t *conf)
{
    for (int i = 0; conf->tetriminos[i] != 0; i++){
        if (conf->tetriminos[i]->width >= conf->width
            || conf->tetriminos[i]->height >= conf->height)
            conf->tetriminos[i]->error =1;
    }
    for (int i = 0; conf->tetriminos[i] != 0; i++)
        if (!conf->tetriminos[i]->error)
            return;
    exit(84);
}

void check_conf(conf_t *conf)
{
    int *to_check = &(conf->key_left);

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            *(to_check + i) == *(to_check + j) && i != j ? exit(84) : 0;
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
    check_tetriminos(conf);
    check_conf(conf);
    if (conf->debug)
        print_conf(conf);
    start_game(conf);
    free(conf);
    return (0);
}
