/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** header
*/

#ifndef _TET_H
#define _TET_H

#include <time.h>
#include <getopt.h>

#define USAGE ""                                                        \
    "Usage: %s [options]\n"                                             \
    "Options:\n"                                                        \
    "  --help                Display this help\n"                       \
    "  -L --level={num}      Start Tetris at level num (def: 1)\n"      \
    "  -l --key-right={K}    Move the tetrimino LEFT using the K key"   \
    " (def: left arrow)\n"                                              \
    "  -r --key-right={K}    Move the tetrimino RIGHT using the K key"  \
    " (def: right arrow)\n"                                             \
    "  -t --key-turn={K}     TURN the tetrimino clockwise 90d using"    \
    " the K key (def: top arrow)\n"                                     \
    "  -d --key-drop={K}     DROP the tetrimino using the K key (def: " \
    "down arrow)\n"                                                     \
    "  -q --key-quit={K}     QUIT the game using the K key (def: "      \
    "'q' key)\n"                                                        \
    "  -p --key-pause={K}    PAUSE/RESTART the game using the K key"    \
    " (def: space bar)\n"                                               \
    "  --map-size={row, col} Set the numbers of rows and columns of"    \
    " the map (def: 20, 10)\n"                                          \
    "  -w --without-next     Hide next tetrimino (def: false)\n"        \
    "  -D --debug            Debug mode (def: false)\n"

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

static struct option tetris_long[] =
{
    {"help", no_argument, 0, 1},
    {"level", required_argument, 0, 'L'},
    {"key-left", required_argument, 0, 'l'},
    {"key-right", required_argument, 0, 'r'},
    {"key-turn", required_argument, 0, 't'},
    {"key-drop", required_argument, 0, 'd'},
    {"key-quit", required_argument, 0, 'q'},
    {"key-pause", required_argument, 0, 'p'},
    {"map-size", required_argument, 0, 2},
    {"without-next", no_argument, 0, 'w'},
    {"debug", no_argument, 0, 'D'},
    {0, 0, 0, 0}
};

conf_t *parse_arguments(int ac, char **av);
void print_conf(conf_t *conf);

#endif
