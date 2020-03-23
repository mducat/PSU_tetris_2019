/*
** EPITECH PROJECT, 2019
** tetris
** File description:
** main
*/

#include <stdlib.h>

#include "tetris.h"

int main(int ac, char **av)
{
    conf_t *conf = parse_arguments(ac, av);

    if (!conf)
        return (84);
    if (conf->debug)
        print_conf(conf);
    free(conf);
    return (0);
}
