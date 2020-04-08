/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** set_utils
*/

#include "mysh.h"
#include "parser.h"
#include "my.h"

static void swap_words(char **tetri, char *tmp, int i, int j)
{
    if (my_strcmp(tetri[i], tetri[j]) > 0) {
        tmp = tetri[j];
        tetri[j] = tetri[i];
        tetri[i] = tmp;
    }
}

static void sort_tab(char **tab)
{
    char *tmp = NULL;
    int len = my_tablen(tab);

    for (int i = 0; i < len; i++)
        for (int j = i + 1; j < len; j++)
            swap_words(tab , tmp, i, j);
}

void show_local_env(sh_t *sh)
{
    if (!sh->var) {
        printf("_\t\n\n");
        return;
    }
    sort_tab(sh->var);
    printf("_\t%s\n\n", sh->previous_line);
    for (int i = 0; sh->var[i]; i++)
        printf("%s\n", sh->var[i]);
}

int create_local_env(char ***local_env)
{
    *local_env = malloc(sizeof(char *) * 1);
    *local_env[0] = NULL;
    return (0);
}
