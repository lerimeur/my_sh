/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** put_in_files.c
*/

#include "history.h"
#include "mysh.h"
#include "my.h"
#include <time.h>

int write_fd(FILE *fd, char *str, char *last_line)
{
    int stock = my_getnbr(last_line) + 1;
    time_t sec;
    struct tm *local;

    time(&sec);
    local = localtime(&sec);
    fseek(fd, 0, SEEK_END);
    fprintf(fd, "\t%d ", stock);
    fprintf(fd, "%d:%d ", local->tm_hour, local->tm_min);
    fprintf(fd, "%s\n", str);
    return (0);
}

char *get_last_line(FILE *fd)
{
    char *buffer = NULL;
    char *buff = NULL;
    size_t len;

    while (getline(&buffer, &len, fd) != -1) {
        if (buff != NULL)
            free(buff);
        buff = strdup(buffer);
    }
    return (buff);
}

void put_in_files(char *input, FILE *fd)
{
    char *last_line = NULL;

    if (input[0] == '!')
        return;
    if (fd == NULL)
        return;
    last_line = get_last_line(fd);
    if (last_line == NULL)
        write_fd(fd, input, "0");
    else
        write_fd(fd, input, last_line);
    fclose(fd);
}
