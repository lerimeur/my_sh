/*
** EPITECH PROJECT, 2018
** my_strdup
** File description:
** String equals to an another
*/

#include <string.h>
#include <stdio.h>

char *my_strdup(char *str)
{
    if (str == NULL)
        return (NULL);
    return (strdup(str));
}
