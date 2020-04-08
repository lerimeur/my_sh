/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** destroy elements
*/

#include "my.h"

void free_tab(char ***ttab)
{
    char **tab = *ttab;

    for (int i = 0; tab[i]; i += 1)
        free(tab[i]);
    free(tab);
    *ttab = NULL;
}

void free_big_tab(char ***tab)
{
    if (tab == NULL)
        return;
    for (int i = 0; tab[i]; i += 1) {
        for (int j = 0; tab[i][j]; j += 1) {
            free(tab[i][j]);
        }
        free(tab[i]);
    }
    free(tab);
}