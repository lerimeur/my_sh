/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** setenv command
*/

#include "mysh.h"
#include "my.h"
#include "parser.h"

int nb_params(char *str)
{
    int spaces = 0;

    if (str == NULL)
        return spaces;
    for (int i = 0; str[i] != '\0'; i += 1)
        if (str[i] == ' ' && str[i + 1] != ' ')
            spaces += 1;
    return (spaces);
}

void get_var(char *str, char **vvar, char **vvalue)
{
    char *var = *vvar;
    char *value = *vvalue;

    if (str[0] == ' ' && str[1] != ' ') {
        if (var == NULL)
            var = &str[1];
        else
            value = &str[1];
    }
    *vvar = var;
    *vvalue = value;
}

static void setenv_get_new_env(char ***env,
char *new_var, char *new_value, int nb_params)
{
    char **params_array = NULL;

    if (nb_params == 1) {
        if (is_in_env(*env, new_var) == true) {
            change_env_var(*env, new_var, NULL, "=");
        } else {
            *env = add_env_var(*env, new_var, new_value, "=");
        }
    } else {
        params_array = str_to_word_array(new_var, " ");
        if (is_in_env(*env, params_array[0]) == true) {
            change_env_var(*env, params_array[0], params_array[1], "=");
        } else {
            *env = add_env_var(*env, params_array[0], params_array[1], "=");
        free_tab(&params_array);
        }
    }
}

void run_setenv(char *params, sh_t *sh)
{
    char *new_var = NULL;
    char *new_value = NULL;

    if (params == NULL || params[0] == '\0')
        return (run_env(new_var, sh));
    if (nb_params(params) > 2) {
        write(1, "setenv: Too many arguments.\n", 28);
        sh->ex = 1;
        return;
    }
    for (int i = 0; params[i]; i += 1)
        get_var(&params[i], &new_var, &new_value);
    if (is_alphanumeric(new_var, "setenv", false) == false) {
        sh->ex = 1;
        return;
    } else {
        setenv_get_new_env(&sh->env, new_var, new_value, nb_params(params));
        sh->ex = 0;
    }
}
