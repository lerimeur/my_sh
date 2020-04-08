/*
** EPITECH PROJECT, 2019
** my_lib
** File description:
** my_strcmp compares two strings
*/

#include "my.h"

int my_strcmp(char *s1, char *s2)
{
    if (!s1 || !s2)
        return (-1);
    return (strcmp(s1, s2));
}

int my_strncmp(char *s1, char *s2, int len)
{
    if (!s1 || !s2 || len <= 0)
        return (-1);
    return (strncmp(s1, s2, len));
}