/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** exec tools
*/

#include "mysh.h"
#include "parser.h"
#include "my.h"

char *get_first_arg(char *str)
{
    int len = 0;
    char *cmd = NULL;

    for (; str[len] && str[len] != ' ' && str[len] != '\t'; len += 1);
    cmd = calloc((len + 1), sizeof(char));
    if (cmd == NULL)
        return (NULL);
    for (int i = 0; i < len; i += 1)
        cmd[i] = str[i];
    cmd[len] = '\0';
    return (cmd);
}

char *get_path(char **env)
{
    if (env == NULL)
        return (NULL);
    for (int i = 0; env[i]; i++) {
        if (my_strncmp("PATH", env[i], 4) == 0 && env[i][4] == '=') {
            return (env[i]);
        }
    }
    return (NULL);
}

static char *clean_path(char *str)
{
    int i = 0;

    if (str == NULL)
        return (NULL);
    while (str[my_strlen(str) - 1] == ':')
        str[my_strlen(str) - 1] = '\0';
    str += 5;
    for (; str[i] == ':'; i++);
    str = my_sprintf("%s%s", "PATH=", &str[i], NULL);
    return (str);
}

static char *search_path(char *full_path, char **paths, char *str, char *path)
{
    for (int i = 0; paths[i]; i++) {
        full_path = my_sprintf("%s/%s", paths[i], str, NULL);
        if ((access(full_path, X_OK) == 0)) {
            free(path);
            free_tab(&paths);
            return (full_path);
        }
        free(full_path);
    }
    return (NULL);
}

char *check_command(char *str, char **env)
{
    char *path = clean_path(get_path(env));
    char **paths = NULL;
    char *full_path = NULL;

    if (path == NULL)
        path = my_strdup("PATH=/bin");
    str = get_first_arg(str);
    if (nb_char(str, '/') > 1 && access(str, X_OK) == 0)
        return (str);
    else if (nb_char(str, '/') > 1 && access(str, X_OK) != 0)
        return (NULL);
    if (path == NULL)
        return (NULL);
    paths = str_to_word_array(&path[5], ":");
    return (search_path(full_path, paths, str, path));
}