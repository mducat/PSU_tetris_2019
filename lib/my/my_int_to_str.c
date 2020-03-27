/*
** EPITECH PROJECT, 2020
** my_int_to_str
** File description:
** Cast int to str
*/

#include <stdlib.h>

#include "my.h"

int get_digit_count(int n)
{
    int len = 0;

    if (n == 0)
        return (1);
    if (n < 0)
        len++;
    while (n != 0){
        len++;
        n /= 10;
    }
    return (len);
}

char *my_int_to_str(int n)
{
    int l = get_digit_count(n);
    int offset = n < 0 ? 1 : 0;
    char *ret = malloc(l + offset + 1);

    ret[l] = 0;
    if (n < 0){
        ret[0] = '-';
        l--;
    }
    while (l--){
        ret[l + offset] = abs(n % 10) + '0';
        n /= 10;
    }
    return (ret);
}
