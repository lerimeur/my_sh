/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** prompt
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "mysh.h"
#include "prompt.h"
#include <glob.h>

int is_glob(char *str, int *glob)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == '$')
            return (0);
        if (str[i] == '*' || str[i] == '?' || str[i] == '[' || str[i] == ']')
            *glob = 1;
    }
    return (*glob);
}

void expand_to_line(char **str)
{
    glob_t globbuf;

    globbuf.gl_offs = 1;
    glob(*str, 0, NULL, &globbuf);
    for (int i = 0; (*str)[i]; i++)
        (*str)[i] = ' ';
    for (long unsigned int i = 0; i < globbuf.gl_pathc; i++) {
        *str = my_realloc(*str, my_strlen(globbuf.gl_pathv[i]) + 1);
        strcat(*str, globbuf.gl_pathv[i]);
        strcat(*str, " ");
    }
}

void call_globbing(char **line)
{
    char **arr = str_to_word_array(*line, " \t");
    int glob = 0;
    int len = 0;

    for (int i = 0; arr[i]; i++) {
        if (is_glob(arr[i], &glob))
            expand_to_line(&arr[i]);
    }
    if (glob) {
        free(*line);
        for (int i = 0; arr[i]; i++)
            len += my_strlen(arr[i]) + 1;
        *line = calloc(len, sizeof(char));
        if (*line == NULL)
            exit(84);
        for (int i = 0; arr[i]; i++)
            strcat(*line, arr[i]);
    }
    free_tab(&arr);
}