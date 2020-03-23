/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** arguments parsing
*/

#include <stdlib.h>
#include <unistd.h>

#include "tetris.h"
#include "my.h"

conf_t *init_conf(void)
{
    conf_t *conf = malloc(sizeof(conf_t));

    if (!conf)
        return (0);
}

void handle_par(conf_t *conf, char c)
{
    switch (c){
    case 'D': conf->debug = 1;
        break;
    case 't': my_printf(optarg);
        break;
    }
}

conf_t *parse_arguments(int ac, char **av)
{
    int c;
    int help;
    conf_t *conf = init_conf();

    if (!conf)
        return (0);
    tetris_long[0].flag = &help;
    while ((c = getopt_long(ac, av, "L:l:r:t:d:q:p:wD", tetris_long, 0)) != -1){
        if (help)
            my_printf(USAGE, av[0]);
        if (c == '?' || help){
            free(conf);
            return (0);
        }
        handle_par(conf, c);
    }
    if (optind < ac)
        write(2, "Remaining arguments !\n", 22);
    return (conf);
}
