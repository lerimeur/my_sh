/*
** EPITECH PROJECT, 2018
** my_rpg
** File description:
** win file
*/

#include "my.h"

static char *my_revstr(char *str)
{
    int len;
    int i = 0;
    char tmp;
    int last;

    len = my_strlen(str) - 1;
    last = len + 1;
    while (i < len) {
        tmp = str[i];
        str[i] = str[len];
        str[len] = tmp;
        i++;
        len--;
    }
    str[last] = '\0';
    return (str);
}

void int_to_str_static(int nb, char *str)
{
    int i = 0;
    int tempo = 0;

    if (nb == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    while (nb > 9) {
        tempo = nb - (nb % 10);
        str[i] = (nb % 10) + 48;
        nb = tempo / 10;
        i++;
    }
    if (nb <= 9) {
        str[i] = nb + 48;
        str[i + 1] = '\0';
    }
    my_revstr(str);
    return;
}