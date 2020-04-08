/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** echo
*/

#include "mysh.h"
#include "my.h"

void run_echo(char *cmd, UNUSED sh_t *sh)
{
    char **av = NULL;

    if (cmd == NULL || cmd[0] == '\0') {
        write(1, "\n", 1);
        return;
    }
    av = str_to_word_array(&cmd[1], " ");
    for (int i = 0; av[i]; i++) {
        write(1, av[i], my_strlen(av[i]));
        if (av[i + 1] != NULL)
            write(1, " ", 1);
    }
    write(1, "\n", 1);
    free_tab(&av);
}
