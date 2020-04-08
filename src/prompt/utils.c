/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** prompt
*/

#include "mysh.h"
#include "prompt.h"
#include <string.h>

void my_putchar_0(char c)
{
    write(0, &c, 1);
}

void my_putstr_0(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        my_putchar_0(str[i]);
}

char *my_revstr(char *str)
{
    int len;
    int i = 0;
    char tmp;
    int last;

    len = strlen(str) - 1;
    last = len + 1;
    while (i < len) {
        tmp = str[i];
        str[i] = str[len];
        str[len] = tmp;
        i++;
        len--;
    }
    str[last] = '\0';
    return (str);
}

void erase_line(sh_t *sh, char **line, int *index, int mode)
{
    if (mode == 1 || mode == 2) {
        my_putchar_0('\r');
        print_prompt(sh);
        for (int i = 0; line[0][i]; i++)
            my_putchar_0(' ');
        for (int i = 0; line[0][i]; i++)
            my_putchar_0('\b');
    }
    if (mode == 2) {
        free(*line);
        *line = calloc(2, sizeof(char));
        *index = 0;
    }
}

int line_is_empty(char *line)
{
    int i = 0;

    while (line[i] != '\0') {
        if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
            return (0);
        i++;
    }
    return (1);
}
