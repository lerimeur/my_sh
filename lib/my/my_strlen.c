/*
** EPITECH PROJECT, 2019
** my_strlen
** File description:
** get size of a string
*/

#include <unistd.h>
#include <string.h>

int my_strlen(char const *str)
{
    if (str == NULL)
        return (0);
    return (strlen(str));
}

int my_nbrlen(long nb)
{
    int ten_power = 1;
    int digits = 0;

    for (; nb > ten_power; ten_power *= 10)
        digits += 1;
    return (digits == 0 ? 1 : digits);
}

int my_tablen(char **tab)
{
    int i = 0;

    for (; tab != NULL && tab[i] != NULL; i++);
    return (i);
}