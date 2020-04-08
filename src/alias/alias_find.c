/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** alias
*/

#include "my.h"
#include "mysh.h"

void find_alias_value(char ***alias, char *var_to_find)
{
    if (alias == NULL)
        return;
    for (int i = 0; alias[i]; i++)
        if (my_strcmp(var_to_find, alias[i][0]) == 0)
            printf("%s\n", alias[i][1]);
}

bool is_in_alias(char ***alias, char *var)
{
    if (alias == NULL)
        return (false);
    for (int i = 0; alias[i]; i++)
        if (my_strcmp(var, alias[i][0]) == 0)
            return (true);
    return (false);
}

void change_alias_var(char ***alias, char **new_alias)
{
    if (alias == NULL)
        return;
    for (int i = 0; alias[i]; i++)
        if (my_strcmp(new_alias[0], alias[i][0]) == 0) {
            free(alias[i][1]);
            alias[i][1] = my_strdup(new_alias[1]);
        }
}
