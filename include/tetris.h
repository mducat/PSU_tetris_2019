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
    "Usage:  %s [options]\n"                                            \
    "Options:\n"                                                        \
    " --help\t\t\tDisplay this help\n"                                  \
    " -L --level={num}\tStart Tetris at level num (def: 1)\n"           \
    " -l --key-right={K}\tMove the tetrimino LEFT using the K key"      \
    " (def: left arrow)\n"                                              \
    " -r --key-right={K}\tMove the tetrimino RIGHT using the K key"     \
    " (def: right arrow)\n"                                             \
    " -t --key-turn={K}\tTURN the tetrimino clockwise 90d using"        \
    " the K key (def: top arrow)\n"                                     \
    " -d --key-drop={K}\tDROP the tetrimino using the K key (def: "     \
    "down arrow)\n"                                                     \
    " -q --key-quit={K}\tQUIT the game using the K key (def: "          \
    "'q' key)\n"                                                        \
    " -p --key-pause={K}\tPAUSE/RESTART the game using the K key"       \
    " (def: space bar)\n"                                               \
    " --map-size={row, col}\tSet the numbers of rows and columns of"    \
    " the map (def: 20, 10)\n"                                          \
    " -w --without-next\tHide next tetrimino (def: false)\n"            \
    " -D --debug\t\tDebug mode (def: false)\n"

#define CPS (10000)

typedef struct tetriminos_s {
    int error;
    int color;
    int width;
    int height;
    char *name;
    char **blocks;
} tetrimino_t;

typedef struct conf {
    tetrimino_t **tetriminos;
    char debug;
    char help;
    char level_start;
    int without_next;
    int key_left;
    int key_right;
    int key_turn;
    int key_drop;
    int key_quit;
    int key_pause;
    int width;
    int height;
} conf_t;

typedef struct cur {
    int cur_x;
    int cur_y;
    int height;
    int width;
    char **blocks;
    tetrimino_t *piece;
} current_t;

typedef struct game {
    int pause;
    int score;
    int high_score;
    int lines;
    int level;
    char **map;
    clock_t timeout;
    clock_t clock;
    current_t *current;
    tetrimino_t *next;
} game_t;

static const struct option tetris_long[] =
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
void print_tetriminos(tetrimino_t **tetris);
void start_game(conf_t *conf);
void display(game_t *game, conf_t *conf);

void draw(game_t *game, conf_t *conf);

void parse_nb(conf_t *conf);
int parse_key(char org);

void chk_conf_game(conf_t *conf);
void check_tet_content(tetrimino_t *piece);

int act(game_t *game, conf_t *conf, int c);
int step(game_t *game, conf_t *conf);
void rotate_blocks(current_t *current, game_t *game, conf_t *conf);

int is_colliding(game_t *game, current_t *current, conf_t *conf);
void merge_map(game_t *game, current_t *current);

int init_piece(game_t *game, conf_t *conf);
tetrimino_t *pick_piece(conf_t *conf);

char **array_dup(char **array, int width);
void free_array(char **array);

int get_high_score(void);
void save_high_score(int high_score);
void lost(void);

void check_lines(game_t *game, conf_t *conf);
int get_mult(int counter);

int get_speed(int level);

int is_map_empty(char **map, int width);

// Tetriminos handling
void set_tetri_int_values(tetrimino_t *tetri, char *content);
int tetri_check_block(tetrimino_t *tetri, char **content);
int set_tetri_content(tetrimino_t *tetri, char **content);
tetrimino_t *get_tetrimino_from_file(char *file);
void sort_tetriminos(tetrimino_t **tetriminos);
int count_int(char *string);
int is_end_string(char *string);
void remove_end_space(char *content);
char *my_str_caps(char *str);
char *get_path(char *file);
char **get_filelist(char *path);
char **get_tetriminos_file(void);
char **read_file_c(char *path);
void pop_array(char ***array, int index);
void push_array(char ***array, char *string);

#endif
