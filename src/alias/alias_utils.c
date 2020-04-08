/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** alias
*/

#include "my.h"
#include "mysh.h"

static void swap_words_big(char ***tetri, char **tmp, int i, int j)
{
    if (my_strcmp(tetri[i][0], tetri[j][0]) > 0) {
        tmp = tetri[j];
        tetri[j] = tetri[i];
        tetri[i] = tmp;
    }
}

static void sort_big_tab(char ***tab)
{
    char **tmp = NULL;
    int len = 0;

    for (int i = 0; tab[i] != NULL; i++, len++);
    for (int i = 0; i < len; i++)
        for (int j = i + 1; j < len; j++)
            swap_words_big(tab , tmp, i, j);
}

void show_alias(sh_t *sh)
{
    if (sh->alias == NULL)
        return;
    sort_big_tab(sh->alias);
    for (int i = 0; sh->alias[i]; i++)
        printf("%s\t(%s)\n", sh->alias[i][0], sh->alias[i][1]);
}
