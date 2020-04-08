/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** set
*/

#include "mysh.h"
#include "parser.h"
#include "my.h"

static void set_get_new_env(char ***local, char ***params, int nb_param)
{
    if (local == NULL || params == NULL)
        return;
    if (nb_param == 1) {
        if (is_in_env(*local, params[0][0]) == true) {
            change_env_var(*local, params[0][0], params[0][1], "\t");
        } else {
            *local = add_env_var(*local, params[0][0], params[0][1], "\t");
        }
        free_big_tab(params);
        return;
    }
    for (int i = 0; params[i]; i++) {
        if (is_in_env(*local, params[i][0]) == true) {
            change_env_var(*local, params[i][0], params[i][1], "\t");
        } else {
            *local = add_env_var(*local, params[i][0], params[i][1], "\t");
        }
    }
    free_big_tab(params);
}

static bool is_command_valid(char **tmp, char ****param, sh_t *sh, int nb_param)
{
    for (int i = 0; tmp[i]; i++)
        if (is_alphanumeric(tmp[i], "set", true) == false) {
            sh->ex = 1;
            return (false);
        }
    for (int i = 0; i != nb_param; i++) {
        (*param)[i] = str_to_word_array(tmp[i], "=");
        if (is_alphanumeric((*param)[i][0], "set", false) == false) {
            sh->ex = 1;
            return (false);
        }
    }
    return (true);

}

void run_set(char *params, sh_t *sh)
{
    char **tmp = NULL;
    int nb_param = nb_params(params);
    char ***params_tab = malloc(sizeof(char **) * (nb_param + 1));

    if (nb_param == 0) {
        show_local_env(sh);
        return;
    }
    tmp = str_to_word_array(&params[1], " ");
    if (is_command_valid(tmp, &params_tab, sh, nb_param) == false)
        return;
    params_tab[nb_param] = NULL;
    set_get_new_env(&sh->var, params_tab, nb_param);
    sh->ex = 0;
}

void run_unset(char *params, sh_t *sh)
{
    char **command = NULL;

    if (params == NULL || params[0] == '\0') {
        write(1, "unset: Too few arguments.\n", 26);
        sh->ex = 1;
        return;
    }
    command = str_to_word_array(&params[1], " ");
    for (int i = 0; command[i]; i++) {
        if (is_in_env(sh->var, command[i]) == true)
            sh->var = remove_env(sh->var, command[i], "\t");
    }
    sh->ex = 0;
    free_tab(&command);
}
