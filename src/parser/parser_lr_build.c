/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** minishell2
*/

#include "mysh.h"
#include "parser.h"
#include "my.h"
#include "prompt.h"

const char *GRAMMAR[] =
{"|", ">>", ">", "<<", "<", NULL};
extern const char *built_in[];

static int fill_node(node_t *node, char *str,
int max_len, sh_t *sh)
{
    int len = 0;
    int index = 0;

    len = get_node_errors(&str, max_len, node);
    if (len < 0)
        return (-ERROR);
    if (len == 0)
        for (; str[len] != '\0'
        && (!check_grammar(&str[len], max_len)); len += 1);
    node->cmd = calloc((len + 1), sizeof(char));
    if (node->cmd == NULL)
        return (-ERROR);
    for (int i = 0; index < len; i += 1) {
        while (str[index] == -1)
            index += 1;
        node->cmd[i] = str[index++];
    }
    for (int i = len; len > 0 && (node->cmd[i] == '\0' ||
    node->cmd[i] == ' ' || node->cmd[i] == '\t'); i -= 1)
        node->cmd[i] = '\0';
    return (check_cmd_validity(node, sh, len, str));
}

static int create_node(node_t **node, char *str,
int max_len, sh_t *sh)
{
    if ((*node)->cmd == NULL)
        return (fill_node((*node), str, max_len, sh));
    if (check_grammar(str, max_len)) {
        (*node)->top = malloc(sizeof(node_t));
        if ((*node)->top == NULL)
            return (ERROR);
        init_node((*node)->top, NULL, *node, NULL);
        (*node) = (*node)->top;
        return (fill_node(*node, str, max_len, sh) + 1);
    } else {
        if ((*node)->right != NULL)
            return (ERROR);
        (*node)->right = malloc(sizeof(node_t));
        if ((*node)->right == NULL)
            return (ERROR);
        init_node((*node)->right, *node, NULL, NULL);
        return (fill_node((*node)->right, str, max_len, sh));
    }
    return (0);
}

static node_t *check_return_tree(node_t *new)
{
    if (new->right)
        new = new->right;
    while (new->top && new->top->cmd[0] != '|' &&
    new->top->left && new->top->right == new)
        if (new->top->left->right)
            new = new->top->left->right;
        else if (new->top->left && !new->top->left->left)
            new = new->top->left;
    if (new && new->cmd[0] == '|') {
        dprintf(2, "Invalid null command.\n");
        return (NULL);
    }
    for (int i = 0; GRAMMAR[i]; i += 1)
        if (my_strncmp(new->cmd, (char *)GRAMMAR[i],
        my_strlen(GRAMMAR[i])) == 0) {
            dprintf(2, "Missing name for redirect.\n");
            return (NULL);
    }
    return (new);
}

static int get_replacements(node_t *new, char **str, sh_t *sh)
{
    int val = 0;

    if (new == NULL || check_cmd_errors(*str, my_strlen(*str)) == ERROR)
        return (ERROR);
    for (; val != ERROR && val != -2; val = get_dollars(str, sh));
    if (val == ERROR || !(*str))
        return (ERROR);
    for (val = 0; val != -2; val = get_tilde(str, sh));
    if (!(*str))
        return (ERROR);
    return (0);
}

node_t *create_tree(char *str, int max_len, sh_t *sh)
{
    node_t *new = malloc(sizeof(node_t));
    int error = 0;

    if (get_replacements(new, &str, sh) == ERROR)
        return (NULL);
    max_len = my_strlen(str);
    init_node(new, NULL, NULL, NULL);
    for (int len = 0; len < max_len; len += 1) {
        for (; (str[len] == ' ' || str[len] == '\t') &&
        len < max_len; len += 1);
        if (len >= max_len)
            break;
        error = create_node(&new, &str[len], max_len, sh);
        if (error <= 0 || new == NULL)
            return (NULL);
        len += error;
    }
    if (str)
        free(str);
    return (check_return_tree(new));
}
