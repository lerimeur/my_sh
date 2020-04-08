/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** prompt
*/

#include "mysh.h"
#include "prompt.h"
#include <string.h>

char *handle_return(sh_t *sh, char **line, int *index)
{
    my_putchar_0('\n');
    if (!line_is_empty(*line)) {
        run_history_seach(*line, sh);
        call_cmd(*line, sh);
        get_termios(sh->env);
    }
    print_prompt(sh);
    *line = calloc(2, sizeof(char));
    *index = 0;
    return (*line);
}

void do_ctrl_a(int *index)
{
    for (int i = *index; i > 0; i--)
        my_putchar_0('\b');
    *index = 0;
}

void do_ctrl_e(sh_t *sh, char **line, int *index)
{
    erase_line(sh, line, index, 1);
    my_putstr_0(*line);
    *index = strlen(*line);
}

char *handle_eof(sh_t *sh, char **line)
{
    if (strlen(*line) == 0)
        return (NULL);
    my_putchar_0('\n');
    my_putchar_0('\r');
    print_prompt(sh);
    my_putstr_0(*line);
    return (*line);
}