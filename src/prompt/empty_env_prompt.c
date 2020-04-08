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

void empty_env_prompt(sh_t *sh)
{
    char *input = NULL;
    size_t size = 100;

    signal(SIGINT, inthandler_empty_env);
    while (42) {
        if (isatty(0))
            write(1, "> ", 2);
        if (getline(&input, &size, stdin) == -1 || input == NULL) {
            write(0, "exit\n", 5);
            exit(sh->ex);
        } else if (input[0] != '\0') {
            input = remove_endline(input);
            if (input == NULL)
                continue;
            call_cmd(input, sh);
        }
    }
    exit(0);
}