/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** parser separator
*/

#include "mysh.h"
#include "parser.h"
#include "my.h"

static const char *SEPARATOR[] = {"&&", "||", ";", NULL};
static const int SEPARATOR_ID[] = {AND, OR, THEN, 0};
static const int SEPARATOR_NB = 3;

static bool is_in_str(char *str, int index)
{
    bool in_str = false;

    for (int i = 0; i < index; i += 1)
        if (str[i] == '"')
            in_str = (in_str ? false : true);
    return (in_str);
}

static int fill_node_command(command_t *node, int block_size,
char *input, int i)
{
    node->cmd = calloc(block_size + 1, sizeof(char));
    if (node->cmd == NULL)
        exit(84);
    for (int tmp = 0; tmp < block_size; tmp += 1)
        node->cmd[tmp] = input[i + tmp];
    return (i + block_size);
}

static int get_node(command_t *node, char *input, int i, int len)
{
    int block_size = 0;

    node->id = NO;
    for (int tmp = 0; !is_in_str(input, i) && tmp < SEPARATOR_NB; tmp += 1)
        if (!my_strncmp((char *)SEPARATOR[tmp], &input[i],
        my_strlen(SEPARATOR[tmp])) && input[i + my_strlen(SEPARATOR[tmp])]
        != SEPARATOR[tmp][0]) {
            node->id = SEPARATOR_ID[tmp];
            i += my_strlen(SEPARATOR[tmp]);
        }
    for (; i < len && (input[i] == ' ' || input[i] == '\t'); i += 1);
    for (bool stp = false; !stp && i + block_size < len; block_size += 1)
        for (int index = 0; index < SEPARATOR_NB; index += 1)
            if (!is_in_str(input, i + block_size) &&
            !my_strncmp((char *)SEPARATOR[index], &input[i + block_size],
        my_strlen(SEPARATOR[index])) && input[i + my_strlen(SEPARATOR[index])]
        != SEPARATOR[index][0]) {
                block_size -= 1;
                stp = true;
            }
    return (fill_node_command(node, block_size, input, i));
}

command_t *get_separator(char *input)
{
    int len = my_strlen(input);
    command_t *new = calloc(1, sizeof(command_t));
    command_t *head = new;

    if (new == NULL)
        exit(84);
    for (int i = 0; i < len; new = new->next) {
        i = get_node(new, input, i, len);
        if (!new->cmd || check_grammar(new->cmd, my_strlen(new->cmd))) {
            dprintf(2, "Invalid null command.\n");
            return (NULL);
        }
        if (i < len) {
            new->next = calloc(1, sizeof(command_t));
            if (!new->next)
                exit(84);
        }
    }
    return (head);
}