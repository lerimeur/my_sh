/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** change value of an env variable for example
*/

#include "mysh.h"
#include "my.h"
#include "parser.h"

char **add_env_var(char **env, char *var, char *new_value, char *deli)
{
    int i = 0;
    int env_len = 0;
    char **new_env = NULL;

    if (env)
        for (; env[env_len]; env_len++);
    new_env = malloc(sizeof(char *) * (env_len + 2));
    for (; i != env_len; i++)
        new_env[i] = my_strdup(env[i]);
    new_env[i] = my_sprintf("%s%s%s", var, deli,
    (new_value == NULL ? "" : new_value));
    new_env[i + 1] = NULL;
    return (new_env);
}

void change_env_var(char **env, char *var, char *new_value, char *deli)
{
    int len = my_strlen(var);

    for (int i = 0; env[i]; i++) {
        if (my_strncmp(var, env[i], len) == 0 && env[i][len] == deli[0]) {
            env[i] = my_sprintf("%s%s%s", var, deli,
            (new_value == NULL ? "" : new_value));
        }
    }
}

char *find_env_value(char *var_to_find, char **env, char delim)
{
    if (env == NULL)
        return NULL;
    for (int i = 0; env[i]; i++) {
        if (my_strncmp(var_to_find, env[i], my_strlen(var_to_find)) == 0
        && env[i][my_strlen(var_to_find)] == delim) {
            return (my_strdup(&env[i][my_strlen(var_to_find) + 1]));
        }
    }
    return (NULL);
}

bool is_in_env(char **env, char *var)
{
    if (env == NULL)
        return (false);
    for (int i = 0; env[i]; i++) {
        if (my_strncmp(var, env[i], my_strlen(var)) == 0)
            return (true);
    }
    return (false);
}
