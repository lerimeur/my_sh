/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** 42sh
*/

#include "mysh.h"
#include "parser.h"
#include "my.h"

extern const char *GRAMMAR[];
extern const char *built_in[];

int check_alias(char **arg_str, sh_t *sh, char **last_cmd)
{
    char *str = *arg_str;
    int len = 0;

    if (sh->alias == NULL)
        return (ERROR);
    for (; str[len] != '\0' && str[len] != ' ' && str[len] != '\t'; len += 1);
    for (int index = 0; sh->alias[index]; index += 1)
        if (len == my_strlen(sh->alias[index][0])
        && my_strncmp(str, sh->alias[index][0],
        my_strlen(sh->alias[index][0])) == 0
        && (!last_cmd || (last_cmd && my_strcmp(sh->alias[index][0],
        *last_cmd)))) {
            *arg_str = replace_in_str(str, sh->alias[index][1],
            0, len - 1);
            *last_cmd = sh->alias[index][0];
            return (0);
        }
    return (ERROR);
}

int check_cmd_errors(char *str, int len)
{
    int parenthesis = 0;

    for (int i = 0; i < len; i += 1) {
        if (str[i] == '(')
            parenthesis += 1;
        else if (str[i] == ')')
            parenthesis -= 1;
    }
    if (parenthesis > 0) {
        dprintf(2, "Too many ('s.\n");
        return (ERROR);
    } else if (parenthesis < 0) {
        dprintf(2, "Too many )'s.\n");
        return (ERROR);
    }
    return (0);
}

int check_errors_matches(char **str, node_t *node,
int max_len, int *len)
{
    if (remove_quotes(*str) == ERROR) {
        dprintf(2, "Unmatched '\"'\n");
        return (-ERROR);
    }
    *len = check_grammar(*str, max_len);
    if (*len && node->left && node->left->left && node->left->cmd[0] != '|') {
        dprintf(2, "Ambiguous output redirect.\n");
        return (-ERROR);
    }
    return (0);
}

int get_node_errors(char **str, int max_len, node_t *node)
{
    int len = 0;
    bool in_grammar = false;

    if (check_errors_matches(str, node, max_len, &len) == -ERROR)
        return (-ERROR);
    for (int i = 0; GRAMMAR[i]; i += 1)
        if (my_strncmp(*str, (char *)GRAMMAR[i], my_strlen(GRAMMAR[i])) == 0)
            in_grammar = true;
    if (in_grammar && (!node->left
    || (node->left->cmd[0] == '|' && !node->left->right)
    || (node->top && node->top->cmd[0] == '|' && node->top->right == node))) {
        dprintf(2, "Invalid null command.\n");
        return (-ERROR);
    }
    return (len);
}

int check_cmd_validity(node_t *node, sh_t *sh,
int len, char *str)
{
    if (((node->top && node->top->cmd[0] == '|')
    || (!node->top && !node->left))
    && ((node->cmd[0] != '!' && check_command(node->cmd, sh->env) == NULL)
    || (node->cmd[0] == '!' &&
    check_command(&node->cmd[1], sh->env) == NULL))) {
        for (int i = 0; built_in[i]; i += 1)
            if (my_strncmp(node->cmd, (char *)built_in[i],
            my_strlen(built_in[i])) == 0)
                return (len - 1);
        for (int i = 0; str[i] && str[i] != ' ' && str[i] != '\t'; i += 1)
            write(2, &str[i], 1);
        write(2, ": Command not found.\n", 21);
        return (-ERROR);
    }
    return (len - 1);
}
