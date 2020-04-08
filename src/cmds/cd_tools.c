/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** cd tools
*/

#include "mysh.h"
#include "my.h"
#include "parser.h"

void find_command_in_alias(char ***alias, char *cmd,
bool show, int *val)
{
    static char *built_in_tab[] = {"exit", "env", "setenv",
    "unsetenv", "cd", "echo", "set", "unset", "alias", "unalias",
    "which", "where", "history", "if", "while", "repeat", NULL};

    for (int i = 0; built_in_tab[i]; i++)
        if (my_strcmp(built_in_tab[i], cmd) == 0) {
            printf((show == true ? "%s is a shell built-in\n"
            : "%s: shell built-in command.\n"), cmd);
            *val += (show == true ? 1 : -10);
        }
    if (is_in_alias(alias, cmd) == true && show == false) {
        printf("%s:\taliased to ", cmd);
        find_alias_value(alias, cmd);
        *val -= 10;
        return;
    } else if (is_in_alias(alias, cmd) == true && show == true) {
        printf("%s is aliased to ", cmd);
        find_alias_value(alias, cmd);
        *val += 1;
    }
}

void my_swap(char **a, char **b)
{
    char *var1 = NULL;

    var1 = *a;
    *a = *b;
    *b = var1;
}

char **get_pwd(char **pwd)
{
    char buf[1024];
    getcwd(buf, 1024);

    pwd = malloc(sizeof(char *) * 3);
    if (pwd == NULL)
        exit(84);
    pwd[0] = my_strdup(buf);
    pwd[1] = "\0";
    pwd[2] = NULL;
    return (pwd);
}

void change_pwd_env(char **env, char oldbuf[])
{
    char buf[1024];
    getcwd(buf, 1024);

    change_env_var(env, "PWD", buf, "=");
    change_env_var(env, "OLDPWD", oldbuf, "=");
}

void error(sh_t *sh, char *line, int status)
{
    if (status == 1) {
        if (errno == ENOTDIR)
            fprintf(stderr, "%s: Not a directory.\n", line);
        else
            fprintf(stderr, "%s: No such file or directory.\n", line);
    } else if (status == 0) {
        if (errno == ENOTDIR)
            fprintf(stderr, "%s: Not a directory.\n", sh->pwd[1]);
        else
            fprintf(stderr, "%s: No such file or directory.\n", sh->pwd[1]);
    }
}