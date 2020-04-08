/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** alias
*/

#include "my.h"
#include "mysh.h"

static void edit_alias(char ****alias, char **new_line, sh_t *sh)
{
    if (my_strcmp(new_line[0], "unalias") == 0
    || my_strcmp(new_line[0], "alias") == 0) {
        printf("%s: Too dangerous to alias that.\n", new_line[0]);
        sh->ex = 1;
        return;
    }
    if (new_line[1][0] == '\0' && is_in_alias(*alias, new_line[0]) == true)
        find_alias_value(*alias, new_line[0]);
    else {
        if (is_in_alias(*alias, new_line[0]) == true)
            change_alias_var(*alias, new_line);
        else if (new_line[1][0] != '\0')
            *alias = add_alias_var(*alias, new_line);
    }
}

void run_alias(char *params, sh_t *sh)
{
    if (params == NULL || params[0] == '\0') {
        show_alias(sh);
        return;
    }
    edit_alias(&sh->alias, split_line(&params[1]), sh);
    sh->ex = 0;
}

void run_unalias(char *params, sh_t *sh)
{
    char **command = NULL;

    if (params == NULL || params[0] == '\0') {
        printf("unalias: Too few arguments.\n");
        sh->ex = 1;
        return;
    }
    if (sh->alias == NULL)
        return;
    command = str_to_word_array(&params[1], " ");
    for (int i = 0; command[i]; i++) {
        if (is_in_alias(sh->alias, command[i]) == true)
            sh->alias = remove_alias(sh->alias, command[i]);
    }
    sh->ex = 0;
    free_tab(&command);
}
