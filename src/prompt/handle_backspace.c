/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** prompt
*/

#include "mysh.h"
#include "prompt.h"
#include <string.h>

char *handle_backspace_2(sh_t *sh, char *line, int *index, int j)
{
    line[j] = '\0';
    my_putchar_0('\r');
    print_prompt(sh);
    my_putstr_0(line);
    my_putstr_0(" \b");
    *index -= 1;
    for (int k = strlen(line); k > *index; k--)
        my_putchar_0('\b');
    return (line);
}

char *handle_backspace(sh_t *sh, char *line, int *index)
{
    char *tmp = NULL;
    int i = 0;
    int j = 0;

    if (*index == 0)
        return line;
    line[*index - 1] = 127;
    tmp = strdup(line);
    for (i = 0; tmp[i]; i++) {
        if (tmp[i] != 127) {
            line[j] = tmp[i];
            j++;
            continue;
        }
    }
    free(tmp);
    return (handle_backspace_2(sh, line, index, j));
}
