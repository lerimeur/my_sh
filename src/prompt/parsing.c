/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** prompt
*/

#include "prompt.h"
#include <string.h>

int is_printable(char c)
{
    if (c == 9)
        return (0);
    if ((c >= '!' && c <= '~') || c == 32)
        return (1);
    return (0);
}

char *my_realloc(char *str, int size_to_add)
{
    int len = strlen(str) + 1;
    char *new_str = calloc((len + size_to_add), sizeof(char));

    strcpy(new_str, str);
    free(str);
    return (new_str);
}
