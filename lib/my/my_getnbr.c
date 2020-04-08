/*
** EPITECH PROJECT, 2018
** my_getnbr
** File description:
** my_getnbr_DAY04
*/

#include "my.h"

int my_getnbr(char const *str)
{
    if (str == NULL)
        return (0);
    return ((int)strtol(str, NULL, 10));
}
