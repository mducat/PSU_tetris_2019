/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** arguments parsing
*/

#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "tetris.h"
#include "my.h"

conf_t *init_conf(void)
{
    conf_t *conf = malloc(sizeof(conf_t));

    if (!conf)
        return (0);
    conf->help = 0;
    conf->debug = 0;
    conf->without_next = 0;
    conf->key_left = KEY_LEFT;
    conf->key_right = KEY_RIGHT;
    conf->key_turn = KEY_UP;
    conf->key_drop = KEY_DOWN;
    conf->key_quit = 'q';
    conf->key_pause = ' ';
    conf->level_start = 1;
    conf->width = 10;
    conf->height = 20;
    return (conf);
}

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
    if (my_strlen(optarg) == 1)
        return (optarg[0]);
    exit(84);
    return (org);
}

void handle_other(conf_t *conf, char c)
{
    int separator = 0;

    switch (c){
    case 'p': conf->key_pause = parse_key(conf->key_pause);
        break;
    case 'w': conf->without_next = 1;
        break;
    case 1: conf->help = 1;
        break;
    case 2: for (; optarg[separator] && optarg[separator] != ','; separator++);
        if (optarg[separator] != ','){
            exit(84);
            return;
        }
        conf->height = my_getnbr(optarg);
        conf->width = my_getnbr(optarg + separator + 1);
        break;
    }
}

void handle_par(conf_t *conf, char c)
{
    switch (c){
    case 'D': conf->debug = 1;
        break;
    case 'L': conf->level_start = my_getnbr(optarg);
        break;
    case 'l': conf->key_left = parse_key(conf->key_left);
        break;
    case 'r': conf->key_right = parse_key(conf->key_right);
        break;
    case 't': conf->key_turn = parse_key(conf->key_turn);
        break;
    case 'd': conf->key_drop = parse_key(conf->key_drop);
        break;
    case 'q': conf->key_quit = parse_key(conf->key_quit);
        break;
    default: handle_other(conf, c);
    }
}

conf_t *parse_arguments(int ac, char **av)
{
    int c;
    conf_t *conf = init_conf();

    if (!conf)
        return (0);
    while ((c = getopt_long(ac, av, "L:l:r:t:d:q:p:wD", tetris_long, 0)) != -1){
        if (c == '?'){
            free(conf);
            return (0);
        }
        handle_par(conf, c);
    }
    if (optind < ac){
        write(2, "Remaining arguments !\n", 22);
        free(conf);
        return (0);
    }
    return (conf);
}
