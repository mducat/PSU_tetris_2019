/*
** EPITECH PROJECT, 2019
** tetris
** File description:
** array
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

void pop_array(char ***array, int index)
{
    char **old_array = *array;
    char **new_array;
    int size = 0;

    for (; old_array[size]; size++);
    if (size < index)
        return;
    new_array = malloc(sizeof(char *) * size);
    if (new_array == NULL)
        exit(84);
    for (int i = 0; old_array[i]; i++)
        if (i != index)
            new_array[i > index ? i - 1 : i] = old_array[i];
    new_array[size - 1] = NULL;
    *array = new_array;
    free(old_array[index]);
    free(old_array);
}

void push_array(char ***array, char *string)
{
    int size = 0;
    char **new_array = NULL;
    char **old_array = *array;

    for (; old_array[size]; size++);
    new_array = malloc(sizeof(char *) * (size + 2));
    if (new_array == NULL)
        exit(84);
    for (int i = 0; old_array[i]; i++)
        new_array[i] = old_array[i];
    new_array[size] = my_strdup(string);
    if (new_array[size] == NULL)
        exit(84);
    new_array[size + 1] = NULL;
    free(old_array);
    *array = new_array;
}

void free_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}
