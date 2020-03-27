/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** high score storage & read
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "my.h"

int get_high_score(void)
{
    int fd = open("highscore.dat", O_RDONLY);
    char data[11];
    ssize_t size = 0;

    if (fd < 0){
        close(fd);
        return (0);
    }
    size = read(fd, data, 10);
    if (size < 0){
        close(fd);
        return (0);
    }
    data[size] = 0;
    close(fd);
    return (my_getnbr(data));
}

void save_high_score(int high_score)
{
    int fd = open("highscore.dat", O_CREAT | O_WRONLY, 0666);
    char *score = my_int_to_str(high_score);

    if (fd < 0)
        return;
    write(fd, score, my_strlen(score));
    close(fd);
}
