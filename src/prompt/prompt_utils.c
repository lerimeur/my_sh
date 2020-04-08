/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** prompt
*/

#include "my.h"
#include "mysh.h"
#include "prompt.h"
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>

void call_exit(char *line, int ex)
{
    free(line);
    my_putstr_0("exit\n");
    exit(ex);
}

void do_tab(sh_t *sh, char **line, int *index)
{
    auto_complete_path(line);
    my_putchar_0('\n');
    print_prompt(sh);
    my_putstr_0(*line);
    *index = my_strlen(*line);
}