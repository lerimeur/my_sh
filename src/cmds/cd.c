/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** change directory
*/

#include "mysh.h"
#include "my.h"
#include "parser.h"

static void new_dir(sh_t *sh, char *line, char buf[])
{
    char buffer[1024];

    if (chdir(line) == -1) {
        error(sh, line, 1);
        sh->ex = 1;
        return;
    } else {
        getcwd(buffer, 1024);
        my_swap(&sh->pwd[0], &sh->pwd[1]);
        sh->pwd[0] = my_strdup(buffer);
        change_pwd_env(sh->env, buf);
        sh->ex = 0;
    }
}

void move_dir_bis(sh_t *sh, char buf[])
{
    my_swap(&sh->pwd[0], &sh->pwd[1]);
    sh->pwd[0] = my_strdup(sh->home);
    change_pwd_env(sh->env, buf);
    chdir(sh->pwd[0]);
}

void move_dir_end(sh_t *sh, char buf[])
{
    my_swap(&sh->pwd[0], &sh->pwd[1]);
    change_pwd_env(sh->env, buf);
}

int nb_char(char *str, char del)
{
    int counter = 1;

    for (int i = 0; str[i]; i++)
        counter += (str[i] == del ? 1 : 0);
    return (counter);
}

void run_cd(char *line, sh_t *sh)
{
    char buf[1024];
    int ac = nb_char(line, ' ');
    *line == ' ' ? line++ : line;

    getcwd(buf, 1024);
    if (ac == 1 && (line[0] == 0)) {
        move_dir_bis(sh, buf);
    } else if (ac == 2 && my_strcmp(line, "-") == 0) {
        if (chdir(sh->pwd[1]) == -1) {
            error(sh, line, 0);
            sh->ex = 1;
        } else {
            move_dir_end(sh, buf);
        }
    } else if (ac == 2) {
        new_dir(sh, line, buf);
    } else {
        fprintf(stderr, "cd: Too many arguments.\n");
        sh->ex = 1;
    }
}
