/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** prompt and call to functions
*/

#include "mysh.h"
#include "parser.h"
#include "history.h"
#include "my.h"

bool is_eq_strict(char *str, char *search)
{
    int len = my_strlen(search);
    int i = 0;

    if (my_strlen(str) < len)
        return (false);
    for (; i < len; i += 1)
        if (str[i] != search[i])
            return (false);
    if (search[i] == '\0' && (str[i] != ' ' && str[i] != '\t'
    && str[i] != '\0'))
        return (false);
    return (true);
}

void call_cmd(char *input, sh_t *sh)
{
    command_t *tab = NULL;
    node_t *tree = NULL;
    char *save_input = my_strdup(input);
    int max = 20;

    tab = init_beg_cmd(input, sh);
    for (; tab; tab = tab->next) {
        if (check_separator(tab, sh) == ERROR)
            break;
        if (!tab->cmd || tab->cmd[0] == '\0' || is_cmd_null(tab->cmd))
            continue;
        for (char *tmp = NULL; max-- > 0 &&
        check_alias(&tab->cmd, sh, &tmp) != ERROR;);
        tree = create_tree(tab->cmd, my_strlen(tab->cmd), sh);
        if (tree == NULL) {
            sh->ex = 1;
            edit_status_value(sh);
            continue;
        }
        get_end_cmd(&tree, sh, save_input, &max);
    }
}
