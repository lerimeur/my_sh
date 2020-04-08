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

int is_filepath(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == '/')
            return (1);
    }
    return (0);
}

int file_match(char *s1, char *s2)
{
    int len = strlen(s2);

    if (strncmp(s1, s2, len) == 0)
        return (1);
    return (0);
}