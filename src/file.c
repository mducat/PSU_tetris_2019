/*
** EPITECH PROJECT, 2019
** tetris
** File description:
** file
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

char *get_path(char *file)
{
    int size = 12;
    char *path;

    for (int i = 0; file[i]; i++, size++);
    path = malloc(sizeof(char) * size);
    for (int i = 0; i < size; i++)
        path[i] = '\0';
    my_strcat(path, "tetriminos/");
    my_strcat(path, file);
    return (path);
}

char **get_filelist(char *path)
{
    DIR *dir;
    struct dirent *ent;
    char **files = malloc(sizeof(char *));

    files[0] = NULL;
    if ((dir = opendir(path)) == NULL) {
        perror("");
        return (0);
    }
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_REG)
            push_array(&files, ent->d_name);
    }
    closedir(dir);
    return (files);
}

char **get_tetriminos_file(void)
{
    char **filelist = get_filelist("tetriminos");
    int point = 0;
    int cmp = 0;
    if (!filelist)
        return (0);
    for (int i = 0; filelist[i]; i++) {
        point = 0;
        for (; filelist[i][point] && filelist[i][point] != '.'; point++);
        if (!filelist[i][point]) {
            pop_array(&filelist, i);
            i -= 1;
            continue;
        }
        if (my_strcmp(filelist[i] + (point + 1), "tetrimino") != 0) {
            pop_array(&filelist, i);
            i -= 1;
            continue;
        }
    }
    return (filelist);
}

char **read_file_c(char *path)
{
    FILE *stream;
    char *line = NULL;
    size_t len;
    ssize_t read;
    char **map = malloc(sizeof(char *));

    map[0] = NULL;
    stream = fopen(path, "r");
    if (stream == NULL) {
        return (NULL);
    }
    while ((read = getline(&line, &len, stream)) != -1)
        push_array(&map, line);
    free(line);
    free(path);
    fclose(stream);
    return (map);
}
