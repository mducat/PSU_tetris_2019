/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** blocks manipulation
*/

#include <stdlib.h>

#include "my.h"

char **array_dup(char **array)
{
    char **dup = 0;
    int size = 0;

    for (; array[size] != NULL; size++);
    dup = malloc(sizeof(char *) * (size + 1));
    if (!dup)
        return (0);
    dup[size] = NULL;
    for (int i = 0; array[i] != NULL; i++){
        dup[i] = my_strdup(array[i]);
        if (!dup[i])
            return (0);
    }
    return (dup);
}
