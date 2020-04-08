/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** which
*/

#include "mysh.h"
#include "my.h"
#include "parser.h"

static void search_path(char **path_list, char *cmd,
bool show_all, int *value)
{
    char *path = NULL;

    for (int i = 0; path_list[i]; i += 1) {
        path = my_sprintf("%s/%s", path_list[i], cmd, NULL);
        if (access(path, X_OK) == 0 && show_all == false) {
            printf("%s\n", (path));
            (*value) += 1;
            free(path);
            return;
        } else if (access(path, X_OK) == 0 && show_all == true) {
            printf("%s\n", (path));
            (*value) += 1;
        } if (path != NULL)
            free(path);
    }
}

void get_correct_path(char **path_list, sh_t *sh, char *cmd, bool show_all)
{
    int value = 0;

    find_command_in_alias(sh->alias, cmd, show_all, &value);
    if (value < 0) {
        sh->ex = 0;
        return;
    }
    search_path(path_list, cmd, show_all, &value);
    sh->ex = 0;
    if (value == 0)
        sh->ex = 1;
    if (value == 0 && show_all == false) {
        printf("%s: Command not found.\n", cmd);
        sh->ex = 1;
    }
}

char **get_path_tab(char **env)
{
    char **paths_list = NULL;
    char *path = NULL;

    for (int i = 0; env != NULL && env[i] != NULL && path == NULL; i += 1)
        path = get_search(env[i], "PATH=");
    paths_list = str_to_word_array(path, ":");
    free(path);
    return (paths_list);
}

void run_which(char *str, sh_t *sh)
{
    char **paths = get_path_tab(sh->env);

    if (access(str, X_OK) == 0 || paths == NULL)
        printf("%s\n", str);
    else if (str[0] == 0) {
        printf("which: Too few arguments.\n");
        sh->ex = 1;
    } else
        get_correct_path(paths, sh, str, false);
    if (paths != NULL)
        free_tab(&paths);
}

void run_where(char *str, sh_t *sh)
{
    char **paths = get_path_tab(sh->env);

    if (access(str, X_OK) == 0 || paths == NULL)
        printf("%s\n", str);
    else if (str[0] == 0) {
        printf("where: Too few arguments.\n");
        sh->ex = 1;
    } else
        get_correct_path(paths, sh, str, true);
    if (paths != NULL)
        free_tab(&paths);
}