/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** parse dollars
*/

#include "mysh.h"
#include "my.h"
#include "parser.h"

static bool get_status(char *str, int *beg)
{
    return (!my_strncmp(&str[*beg], "$? ", 3)
    || !my_strncmp(&str[*beg], "$?\t", 3)
    || !my_strncmp(&str[*beg], "$?\n", 3)
    || !my_strncmp(&str[*beg], "$?\0", 3));
}

static int get_value(char *str, int *beg, int *len, char **buffer)
{
    bool is_in_str = false;

    for (; str[*beg] != '\0' && str[*beg] != '$'; *beg += 1)
        if (str[*beg] == '\"' || str[*beg] == '\'')
            is_in_str = (is_in_str ? false : true);
    if (is_in_str || str[*beg] != '$' || str[*beg + 1] == ' '
    || str[*beg + 1] == '\t')
        return (-2);
    for (*len = *beg; str[*len] != '\0' && str[*len + 1] != ' '
    && str[*len + 1] != '\t' && str[*len + 1] != ':'; *len += 1);
    *len -= *beg;
    if (get_status(str, beg))
        *buffer = my_strdup("status");
    else {
        *buffer = calloc((*len + 1), sizeof(char));
        if (!(*buffer))
            return (ERROR);
        for (int i = 0; i < *len; i += 1)
            (*buffer)[i] = str[i + *beg + 1];
    }
    return (0);
}

int get_dollars(char **arg_str, sh_t *sh)
{
    char *result = NULL;
    char *buffer = "\0";
    int beg = 0;
    int len = 0;

    for (int x = get_value(*arg_str, &beg, &len, &buffer); x || !buffer;)
        return (x);
    result = find_env_value(buffer, sh->var, '\t');
    if (result == NULL)
        result = find_env_value(buffer, sh->env, '=');
    if (result == NULL) {
        if ((*arg_str)[beg + 1] == '(')
            dprintf(2, "Illegal variable name.\n");
        else
            dprintf(2, "%s: Undefined variable.\n", buffer);
        free(buffer);
        return (ERROR);
    }
    free(buffer);
    *arg_str = replace_in_str((*arg_str), result, beg, len);
    return (0);
}