/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** builtins_hub_
*/

#include "mysh.h"
#include "get_next_line.h"
#include "parser.h"
#include "my.h"

static const int tree_index[14] = {4, 4, 6, 8, 2, 4, 3, 5, 5, 7, 6, 6, 0, -1};
const char *built_in[] = {"exit", "env", "setenv", "unsetenv", "cd", "echo",
"set", "unset", "alias", "unalias", "which", "where", "history", NULL};

void call_execution(node_t *tree, sh_t *sh)
{
    int pid = 0;
    int value = 0;
    int status = 0;

    pid = fork();
    if (pid == -1)
        exit(-1);
    else if (pid == 0) {
        tree = go_to_top(tree);
        value = run_exec(tree, sh->env, 1);
        exit(value);
    } else {
        wait(&status);
        check_child_errors(status);
    }
    sh->ex = status / 256;
}

void get_cmd(node_t *tree, sh_t *sh)
{
    static void (*array_function[])(char *line, sh_t *sh)
    = {&run_exit, &run_env, &run_setenv, &run_unsetenv, &run_cd,
    &run_echo, &run_set, &run_unset, &run_alias, &run_unalias,
    &run_which, &run_where, &run_history, NULL};
    int value = 0;

    if (tree->cmd == NULL)
        value = -1;
    if (tree->top == NULL) {
        for (int i = 0; built_in[i]; i++)
            if (is_eq_strict(tree->cmd, (char *)built_in[i]) == true) {
                array_function[i](&tree->cmd[tree_index[i]], sh);
                value++;
            }
    }
    if (value <= 0)
        call_execution(tree, sh);
}
