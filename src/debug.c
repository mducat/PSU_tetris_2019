/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** debug mode
*/

#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>

#include "tetris.h"
#include "my.h"

void wait_key(void)
{
    struct termios term;
    char c;

    ioctl(0, TCGETS, &term);
    term.c_lflag &= ~(ECHO | ICANON);
    ioctl(0, TCSETS, &term);
    read(0, &c, 1);
    term.c_lflag |= (ECHO | ICANON);
    ioctl(0, TCSETS, &term);
}

char *key_to_str(int key)
{
    char *char_str;

    if (key == ' ')
        return ("(space)");
    if (key == KEY_RIGHT)
        return ("^EOC");
    if (key == KEY_LEFT)
        return ("^EOD");
    if (key == KEY_UP)
        return ("^EOA");
    if (key == KEY_DOWN)
        return ("^EOB");
    char_str = malloc(2 * sizeof(char));
    char_str[1] = 0;
    char_str[0] = key;
    return (char_str);
}

void print_conf(conf_t *conf)
{
    my_printf("*** DEBUG MODE ***\n");
    my_printf("Key Left :  %s\n", key_to_str(conf->key_left));
    my_printf("Key Right :  %s\n", key_to_str(conf->key_right));
    my_printf("Key Turn :  %s\n", key_to_str(conf->key_turn));
    my_printf("Key Drop :  %s\n", key_to_str(conf->key_drop));
    my_printf("Key Quit :  %s\n", key_to_str(conf->key_quit));
    my_printf("Key Pause :  %s\n", key_to_str(conf->key_pause));
    my_printf("Next :  %s\n", conf->without_next ? "No" : "Yes");
    my_printf("Level :  %d\n", conf->level_start);
    my_printf("Size :  %d*%d\n", conf->height - 1, conf->width - 1);
    print_tetriminos(conf->tetriminos);
    my_printf("Press any key to start Tetris\n");
    wait_key();
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
