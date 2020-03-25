/*
** EPITECH PROJECT, 2019
** tetris
** File description:
** tetriminos
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

void set_tetri_int_values(tetrimino_t *tetri, char *content)
{
    int index = 0;

    tetri->width = my_getnbr(content);
    for (index = 0; content[index] != ' '
        || !(content[index + 1] >= '0'
        && content[index + 1] <= '9'); index++);
    tetri->height = my_getnbr(content + index + 1);
    for (index += 1; content[index] != ' '
        && !(content[index + 1] >= '0'
        && content[index + 1] <= '9'); index++);
    tetri->color = my_getnbr(content + index + 1);
}

int tetri_check_block(tetrimino_t *tetri, char **content)
{
    for (int i = 1; i < tetri->height + 1; i++) {
        remove_end_space(content[i]);
        if (my_strlen(content[i]) > tetri->width)
            return (1);
    }
    return (0);
}

int set_tetri_content(tetrimino_t *tetri, char **content)
{
    int int_count = 0;

    if (content[0] == NULL)
        return (1);
    int_count = count_int(content[0]);
    if (int_count != 3)
        return (1);
    set_tetri_int_values(tetri, content[0]);
    for (int_count = 0; content[int_count]; int_count++);
    if (int_count != (tetri->height + 1) || tetri_check_block(tetri, content))
        return (1);
    tetri->blocks = malloc(sizeof(char *) * (tetri->height + 1));
    for (int i = 1; i < tetri->height + 1; i++)
        tetri->blocks[i - 1] = my_strdup(content[i]);
    tetri->blocks[tetri->height] = NULL;
    return (0);
}

tetrimino_t *get_tetrimino_from_file(char *file)
{
    char **file_content = read_file_c(get_path(file));
    tetrimino_t *tetri = malloc(sizeof(tetrimino_t));
    int name_s = 0;
    int line_c = 0;

    for (; file[name_s] != '.'; name_s++);
    file[name_s] = '\0';
    tetri->name = file;
    if (file_content == NULL)
        tetri->error = 1;
    else
        tetri->error = set_tetri_content(tetri, file_content);
    return (tetri);
}

void sort_tetriminos(tetrimino_t **tetriminos)
{
    int count = 0;
    tetrimino_t *tmp = NULL;
    char *str1 = NULL;
    char *str2 = NULL;
    for (; tetriminos[count]; count++);
    if (count <= 1)
        return;
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            str1 = my_str_caps(tetriminos[i]->name);
            str2 = my_str_caps(tetriminos[j]->name);
            if (my_strcmp(str1, str2) > 0) {
                tmp = tetriminos[i];
                tetriminos[i] = tetriminos[j];
                tetriminos[j] = tmp;
            }
            free(str1);
            free(str2);
        }
    }
}
