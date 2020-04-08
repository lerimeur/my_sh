/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** utils
*/

#include "my.h"
#include <stdio.h>

void my_show_tab(char **tab)
{
    for (int i = 0; tab[i]; i++) {
        printf("'%s'", tab[i]);
        printf("%s", "\n");
    }
}

void my_show_big_tab(char ***tab)
{
    for (int i = 0; tab[i]; i++) {
        my_show_tab(tab[i]);
        printf("%s", "\n");
    }
}

char *remove_endline(char *str)
{
    if (my_strcmp(str, "\n") == 0)
        return (NULL);
    for (int i = 0; str[i]; i++)
        if (str[i] == '\n')
            str[i] = '\0';
    return (str);
}