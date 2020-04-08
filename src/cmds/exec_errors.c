/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** exec_errors
*/

#include "mysh.h"

void check_child_errors(int status)
{
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGSEGV)
            fprintf(stderr, "Segmentation fault");
        else if (WTERMSIG(status) == SIGFPE)
            fprintf(stderr, "Floating exception");
    }
    if (WCOREDUMP(status))
        fprintf(stderr, " (core dumped)");
    if (WCOREDUMP(status) || WIFSIGNALED(status))
        fprintf(stderr, "\n");
}
