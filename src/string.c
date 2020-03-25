/*
** EPITECH PROJECT, 2019
** tetris
** File description:
** string
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

int count_int(char *string)
{
    int count = 0;

    for (int i = 0; string[i]; i++) {
        if (i > 0 && string[i] == ' '
            && (string[i - 1] >= '0' && string[i - 1] <= '9'))
            count++;
        else if ((string[i + 1] == '\n' || !string[i + 1])
            && string[i] >= '0' && string[i] <= '9')
            count++;
    }
    return (count);
}

int is_end_string(char *string)
{
    int i = 0;
    for (; string[i] && string[i] == ' '; i++);
    if (string[i])
        return (0);
    return (1);
}

void remove_end_space(char *content)
{
    int i = 0;

    for (i = my_strlen(content) - 1; i > 0 &&
        (content[i] == '\n' || content[i] == ' '); i--) {
        content[i] = 0;
    }
}

char *my_str_caps(char *str)
{
    char *new_str = my_strdup(str);

    for (int i = 0; new_str[i]; i++) {
        if (new_str[i] >= 'a' && new_str[i] <= 'z')
            new_str[i] = new_str[i] - 32;
    }
    return (new_str);
}
