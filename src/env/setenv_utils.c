/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** setenv command
*/

#include "mysh.h"
#include "my.h"
#include "parser.h"

static bool is_is_alphanumeric_bis(int i, int e, char *var, char *built_in)
{
    while (i++ < e - 1) {
        if (var[i] < '0' || var[i] > 'z' || (var[i] < 'A' && var[i] > '9')) {
            printf("%s: Variable name must contain alphanumeric characters.\n",
            built_in);
            return (false);
        }
        if ((var[i] > 'Z' && var[i] != '_' && var[i] < 'a')) {
            printf("%s: Variable name must contain alphanumeric characters.\n",
            built_in);
            return (false);
        }
    }
    return (true);
}

bool is_alphanumeric(char *var, char *built_in, bool just_first_index)
{
    int i = 0;
    int e = 0;

    if ((var[0] < 'A' || (var[0] > 'Z' && var[0] < 'a') || var[0] > 'z')
    && var[0] != '_') {
        printf("%s: Variable name must begin with a letter.\n", built_in);
        return (false);
    }
    if (just_first_index == true)
        return (true);
    for (i = 0; var[i] == ' ' || var[i] == '\t'; i += 1);
    for (e = i; var[e] != ' ' && var[e] != '\t' && var[e] != '\0'; e += 1);
    return (is_is_alphanumeric_bis(i, e, var, built_in));
}