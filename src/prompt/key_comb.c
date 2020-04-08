/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** prompt
*/

#include "prompt.h"
#include <string.h>

void do_clear(sh_t *sh, char **line)
{
    my_putstr_0("\033c");
    print_prompt(sh);
    my_putstr_0(*line);
}

void handle_arrows(sh_t *sh, char buff[10], char **line, int *index)
{
    if (buff[2] == 65)
        go_in_history(sh, -1, line, index);
    if (buff[2] == 66)
        go_in_history(sh, 1, line, index);
    if (buff[2] == 68 && *index > 0) {
        my_putchar_0('\b');
        *index -= 1;
    }
    if (buff[2] == 67 && line[0][*index]) {
        my_putchar_0(line[0][*index]);
        *index += 1;
    }
}
