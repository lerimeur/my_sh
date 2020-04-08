/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** prompt
*/

#include <string.h>
#include "my.h"
#include "prompt.h"
#include "mysh.h"

sh_t *get_sh_var(int mode, sh_t *sh)
{
    static sh_t *tmp = NULL;

    if (mode == 1) {
        tmp = sh;
        return (NULL);
    }
    else if (mode == 2)
        return (tmp);
    return (NULL);
}

void inthandler(int sg)
{
    sh_t *tmp = get_sh_var(2, NULL);

    if (ISATTY_0 && sg) {
        my_putstr_0("\r");
        print_prompt(tmp);
        my_putstr_0(" \n");
        print_prompt(tmp);
    }
}

void inthandler_empty_env(int sg)
{
    if (isatty(0) == 1 && sg)
        my_putstr_0("\r>   \n\r> ");
}

void print_prompt(sh_t *sh)
{
    char *str = BOLD CYAN "42SH " MAG;
    char *str2 = NORMAL " $ ";
    int user_len = my_strlen(sh->user) + 6;

    write(1, str, my_strlen(str));
    if (((int)my_strlen(sh->pwd[0]) >= user_len)) {
        if (strncmp(sh->pwd[0], sh->home, my_strlen(sh->home)) == 0) {
            write(1, "~/" FLAT, 2);
            write(1, &sh->pwd[0][user_len + 1],
            my_strlen(&sh->pwd[0][user_len]));
        }
        else
            write(1, "~" FLAT, 1);
    }
    else
        write(0, sh->pwd[0], my_strlen(sh->pwd[0]));
    write(0, str2, my_strlen(str2));
}
