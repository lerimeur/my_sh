/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** shell
*/

#include "mysh.h"
#include "parser.h"
#include "my.h"

extern const char *GRAMMAR[];
extern const char *built_in[];

int check_grammar(char *str, int max_len)
{
    int len = my_strlen(str);
    int count_str = 0;

    len = max_len - len;
    for (int i = len; i > 0; i -= 1)
        if (str[-i] == '"' || str[-i] == '\'')
            count_str += 1;
    if (count_str % 2 != 0)
        return (0);
    for (int i = 0; GRAMMAR[i] != NULL; i += 1)
        if (my_strncmp(str, (char *)GRAMMAR[i], my_strlen(GRAMMAR[i])) == 0)
            return (my_strlen(GRAMMAR[i]));
    return (0);
}

void init_node(node_t *node, node_t *top, node_t *left, node_t *right)
{
    node->top = top;
    node->left = left;
    node->right = right;
    node->cmd = NULL;
}

int remove_quotes(char *str)
{
    int quote_nb = 0;
    int len = my_strlen(str);

    for (int i = 0; i < len; i += 1)
        if (str[i] == '\"')
            quote_nb += 1;
    if (quote_nb % 2 != 0)
        return (ERROR);
    for (int i = 0; i < len; i += 1)
        if (i >= 1 && str[i - 1] == '\\')
            str[i - 1] = -1;
        else if (str[i] == '"')
            str[i] = -1;
    return (0);
}

char *replace_in_str(char *str, char *result, int beg, int len)
{
    char *buffer = NULL;
    int index = 0;

    buffer = calloc((my_strlen(result) +
    (my_strlen(str) - len) + 1), sizeof(char));
    if (buffer == NULL)
        return (NULL);
    for (int i = 0; i < beg; i += 1)
        buffer[index++] = str[i];
    for (int i = 0; i < my_strlen(result); i += 1)
        buffer[index++] = result[i];
    for (int i = beg + len + 1; i < my_strlen(str); i += 1)
        buffer[index++] = str[i];
    return (buffer);
}

int get_tilde(char **arg_str, sh_t *sh)
{
    char *str = *arg_str;
    char *result = NULL;
    int beg = 0;
    bool is_in_str = false;

    for (; str[beg] != '\0' && str[beg] != '~'; beg += 1)
        if (str[beg] == '\"' || str[beg] == '\'')
            is_in_str = (is_in_str ? false : true);
    if (is_in_str || str[beg] != '~' || !sh->home)
        return (-2);
    result = sh->home;
    *arg_str = replace_in_str(str, result, beg, 0);
    return (0);
}
