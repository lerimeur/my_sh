/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** alias
*/

#include "my.h"
#include "mysh.h"

static void add_last_line(char ****new, int i, char **new_alias)
{
    (*new)[i] = malloc(sizeof(char *) * 3);
    (*new)[i][0] = my_strdup(new_alias[0]);
    (*new)[i][1] = my_strdup(new_alias[1]);
    (*new)[i][2] = NULL;
    (*new)[i + 1] = NULL;
}

char ***add_alias_var(char ***alias, char **new_alias)
{
    int i = 0;
    int alias_len = 0;
    char ***new = NULL;

    if (alias == NULL) {
        new = malloc(sizeof(char **) * 2);
    } else {
        for (; alias[alias_len]; alias_len++);
        new = malloc(sizeof(char **) * (alias_len + 2));
        for (; i != alias_len; i++) {
            new[i] = malloc(sizeof(char *) * 3);
            new[i][0] = my_strdup(alias[i][0]);
            new[i][1] = my_strdup(alias[i][1]);
            new[i][2] = NULL;
        }
    }
    add_last_line(&new, i, new_alias);
    free_big_tab(alias);
    return (new);
}

char ***remove_alias(char ***alias, char *command)
{
    int i = 0;
    int j = 0;
    int alias_len = 0;
    char ***new = NULL;

    for (;alias[alias_len]; alias_len++);
    new = malloc(sizeof(char **) * (alias_len));
    for (; i != alias_len;) {
        if (my_strcmp(alias[i][0], command) == 0)
            i++;
        else {
            new[j] = malloc(sizeof(char *) * 3);
            new[j][0] = my_strdup(alias[i][0]);
            new[j][1] = my_strdup(alias[i++][1]);
            new[j++][2] = NULL;
        }
    }
    free_big_tab(alias);
    new[i - 1] = NULL;
    return (new);
}
