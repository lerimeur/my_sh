/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** unsetenv
*/

#include "mysh.h"
#include "my.h"
#include "parser.h"

char **remove_env(char **env, char *command, char *deli)
{
    int i = 0;
    int j = 0;
    int env_len = 0;
    char **new_env;

    for (int i = 0; env[i]; env_len++, i++);
    new_env = malloc(sizeof(char *) * (env_len));
    for (; i != env_len;) {
        if (my_strncmp(command, env[i], my_strlen(command)) == 0
        && env[i][my_strlen(command)] == deli[0])
            i++;
        else
            new_env[j++] = my_strdup(env[i++]);
    }
    free_tab(&env);
    new_env[i - 1] = NULL;
    return (new_env);
}

void run_unsetenv(char *params, sh_t *sh)
{
    char **command = NULL;

    if (params == NULL || params[0] == '\0') {
        write(1, "unsetenv: Too few arguments.\n", 29);
        sh->ex = 1;
        return;
    }
    command = str_to_word_array(&params[1], " ");
    for (int i = 0; command[i]; i++) {
        if (is_in_env(sh->env, command[i]) == true)
            sh->env = remove_env(sh->env, command[i], "=");
    }
    sh->ex = 0;
    free_tab(&command);
}
