/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** lr_tools
*/

#include "mysh.h"
#include "my.h"

bool my_strbeg_eq(char *str, char const *cmp)
{
    int len = my_strlen(cmp);
    int index = 0;

    for (; (index < len) && (str[index] == cmp[index]); index += 1);
    return (index < len ? false : true);
}

void destroy_tree(node_t **tree)
{
    node_t *node = *tree;

    for (; node->top != NULL; node = node->top);
    while (node != NULL) {
        if (node->right != NULL)
            free(node->right);
        if (node->top != NULL)
            free(node->top);
        node = node->left;
    }
    return;
}

node_t *get_next_node(node_t *node)
{
    if (node == NULL)
        return (NULL);
    if ((node->top != NULL) && (node->top->right != node))
        return (node->top->right);
    if ((node->top != NULL) && (node->top->top != NULL) &&
    (node->top->right == node))
        return (node->top->top->right);
    return (NULL);
}

node_t *get_prev_node(node_t *node)
{
    if (node == NULL)
        return (NULL);
    if (node->top && node->top->cmd[0] != '|'
    && node->top->right == node && node->top->left
    && node->top->left->right)
        return (node->top->left->right);
    if (node->top && node->top->left && node->top->left != node) {
        if (node->top->left->right)
            return (node->top->left->right);
        else if (node->top->left->cmd[0] != '|')
            return (node->top->left);
    }
    return (NULL);
}

node_t *go_to_top(node_t *node)
{
    for (; node->top != NULL && node->top->cmd[0] == '|'; node = node->top);
    if (node->right != NULL)
        node = node->right;
    return (node);
}
