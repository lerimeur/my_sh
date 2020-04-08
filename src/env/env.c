/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** env function
*/

#include "mysh.h"
#include "my.h"

void run_env(UNUSED char *cmd, sh_t *sh)
{
    for (int i = 0; sh->env[i]; i++)
        printf("%s\n", sh->env[i]);
}
