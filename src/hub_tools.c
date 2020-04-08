/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** hub tools
*/

#include "mysh.h"
#include "parser.h"
#include "my.h"
#include "history.h"
#include "prompt.h"

bool is_cmd_null(char *cmd)
{
    for (int i = 0; cmd[i] != '\0'; i += 1)
        if (cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != '\n')
            return (false);
    return (true);
}

void edit_status_value(sh_t *sh)
{
    char buffer[1024];

    if (is_in_env(sh->var, "status") == true) {
        int_to_str_static(sh->ex, buffer);
            change_env_var(sh->var, "status", buffer, "\t");
    }
}

int check_separator(command_t *cmd, sh_t *sh)
{
    if (cmd->id == AND && sh->ex != 0)
        return (ERROR);
    if (cmd->id == OR && sh->ex == 0)
        return (ERROR);
    return (0);
}

void get_end_cmd(node_t **tree, sh_t *sh, char *save_input, int *max)
{
    call_globbing(&(*tree)->cmd);
    (*tree)->cmd = clean_str(&(*tree)->cmd);
    get_cmd(*tree, sh);
    destroy_tree(tree);
    sh->previous_line = save_input;
    (*max) = 20;
    edit_status_value(sh);
}

command_t *init_beg_cmd(char *input, sh_t *sh)
{
    command_t *tabl = NULL;

    put_in_files(input, set_up_file(sh->env));
    input = check_history_call(&input, sh);
    input = clean_str(&input);
    tabl = get_separator(input);
    if (tabl == NULL)
        sh->ex = 1;
    return (tabl);
}
