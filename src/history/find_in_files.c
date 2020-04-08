/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** find_in_files.c
*/

#include "history.h"
#include "mysh.h"
#include "my.h"
#include <ctype.h>

char *parser_command(char *str)
{
    int i = 0;

    for (i = 0; ((str[i] >= '0' && str[i] <= '9') ||
        str[i] == ' ' || str[i] == '\t' || str[i] == ':'); i++);
    return (str + i);
}

char *find_number(FILE *fd, char *str)
{
    char *buffer = NULL;
    size_t len;
    int stock = 0;
    int nb = my_getnbr(str);

    while (getline(&buffer, &len, fd) != -1) {
        stock = my_getnbr(buffer);
        if (stock == nb)
            return (parser_command(buffer));
    }
    return NULL;
}

char *find_name(FILE *fd, char *input)
{
    int i = 0;
    int stock = 0;
    size_t len = 0;
    size_t len_2 = my_strlen(input);
    char *buff = NULL;
    char *buffer = NULL;

    while (getline(&buffer, &len, fd) != -1) {
        for (i = 0; ((buffer[i] >= '0' && buffer[i] <= '9') ||
        buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == ':'); i++);
        if (my_strncmp(buffer + i, input, len_2) == 0) {
            if (buff != NULL)
                free(buff);
            buff = strdup(buffer);
            stock = i - 1;
        }
    }
    return (buff + stock);
}

char *find_in_files(FILE *fd, char *input)
{
    if (input[0] >= '0' && input[0] <= '9' && input[1] == '\0')
        return (find_number(fd, input));
    else
        return (find_name(fd, input));
    return NULL;
}
