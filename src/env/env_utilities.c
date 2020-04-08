/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Utility functions in regard to the env.
*/

#include "mysh.h"
#include "my.h"

int load_env(char **env, sh_t *sh)
{
    int len = 0;

    if (env == NULL)
        return 84;
    for (; env[len]; len += 1);
    sh->env = malloc(sizeof(char *) * (len + 1));
    if (sh->env == NULL)
        return (84);
    sh->env[len] = NULL;
    for (int i = 0; i < len; i += 1)
        sh->env[i] = my_strdup(env[i]);
    return (create_local_env(&sh->var));
}
