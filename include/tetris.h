/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** header
*/

#ifndef _TET_H
#define _TET_H

typedef struct piece {
    char error;
    char color;
    int width;
    int size;
    char **blocks;
} tetrimino_t;

typedef struct conf {
    tetrimino_t **tetriminos;
    char debug;
    char without_next;
    char key_left;
    char key_right;
    char key_turn;
    char key_drop;
    char key_quit;
    char key_pause;
    int width;
    int height;
} conf_t;

typedef struct game {
    int score;
    int high_score;
    int lines;
    int level;
    char **map;
    clock_t clock;
    tetrimino_t *current;
    tetrimino_t *next;
} game_t;

#endif
