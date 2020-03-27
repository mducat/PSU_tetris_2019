/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** parse args
*/

#include <stdlib.h>
#include <ncurses.h>

#include "tetris.h"
#include "my.h"

int parse_key(char org)
{
    if (!my_strcmp(optarg, "left arrow"))
        return (KEY_LEFT);
    if (!my_strcmp(optarg, "right arrow"))
        return (KEY_RIGHT);
    if (!my_strcmp(optarg, "up arrow"))
        return (KEY_UP);
    if (!my_strcmp(optarg, "down arrow"))
        return (KEY_DOWN);
    if (!my_strcmp(optarg, "space"))
        return (' ');
    if (my_strlen(optarg) == 1)
        return (optarg[0]);
    exit(84);
    return (org);
}

void parse_nb(conf_t *conf)
{
    int separator = 0;

    for (; optarg[separator] && optarg[separator] != ','; separator++);
    if (optarg[separator] != ',' || !separator || !optarg[separator + 1]){
        exit(84);
        return;
    }
    for (int i = 0; i < separator; i++)
        if (!is_num(optarg[i]))
            exit(84);
    for (int i = separator + 1; optarg[i] != 0; i++)
        if (!is_num(optarg[i]))
            exit(84);
    conf->height = my_getnbr(optarg) + 1;
    conf->width = my_getnbr(optarg + separator + 1) + 1;
}

