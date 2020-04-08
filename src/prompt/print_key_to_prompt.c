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

int print_key_in_middle(sh_t *sh, char **line, int *index, char buff[10])
{
    char *tmp = NULL;
    int i = 0;

    erase_line(sh, line, index, 1);
    tmp = strdup(*line);
    *line = my_realloc(*line, 1);
    for (i = 0; i < *index; i++)
        (*line)[i] = tmp[i];
    (*line)[i] = buff[0];
    for (; tmp[i]; i++)
        (*line)[i + 1] = tmp[i];
    (*line)[i + 1] = '\0';
    *index += 1;
    free(tmp);
    return (i);
}

char *print_key(sh_t *sh, char *line, char buff[10], int *index)
{
    int i = 0;

    if (line[*index] == '\0') {
        line = my_realloc(line, 1);
        line[*index] = buff[0];
        line[*index + 1] = '\0';
        *index += 1;
    }
    else
        i = print_key_in_middle(sh, &line, index, buff);
    my_putchar_0('\r');
    print_prompt(sh);
    my_putstr_0(line);
    for (; i >= *index; i--)
        my_putchar_0('\b');
    return (line);
}