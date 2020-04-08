/*
** EPITECH PROJECT, 2019
** CPE_getnextline_2018
** File description:
** Gets next line
*/

#include "my.h"

static char *my_realloc(char *str, size_t size)
{
    char *new = NULL;
    int len = 0;
    int count = 0;

    if (str != NULL)
        for (; str[len] != '\0'; len += 1);
    size += len;
    new = calloc(size, sizeof(char));
    if (new == NULL)
        return (NULL);
    if (str != NULL) {
        for (; str[count] != '\0'; count += 1)
            new[count] = str[count];
        new[count] = '\0';
        free(str);
    }
    for (; count < size; count += 1)
        new[count] = '\0';
    return (new);
}

static char *fill_strings(char *buff, char *temp, int buff_len)
{
    char *line = NULL;
    int b_count = 0;
    int count = 0;

    for (; temp[count] != '\n' && temp[count]; count += 1);
    line = calloc((count + 1), sizeof(char));
    if (line == NULL)
        return (NULL);
    for (int i = 0; i <= count; i += 1)
        line[i] = temp[i];
    line[count] = '\0';
    for (int i = 0; i < READ_SIZE + 2; i += 1)
        buff[i] = '\0';
    for (count += 1; b_count <= READ_SIZE + 2 && temp[count]; b_count += 1) {
        buff[b_count] = temp[count];
        count += 1;
    }
    for (int i = b_count; i < READ_SIZE + 2; i += 1)
        buff[i] = '\0';
    return (line);
}

static char *my_strcat(char *buff, char *line)
{
    char *tmp = NULL;
    int count = 0;
    int line_len = 0;
    int buff_len = 0;

    for (; line != NULL && line[line_len] != '\0'; line_len += 1);
    for (; buff_len <= READ_SIZE + 2 && buff[buff_len] != '\0'; buff_len += 1);
    tmp = calloc((buff_len + line_len + 2), sizeof(char));
    if (tmp == NULL)
        return (NULL);
    for (int i = 0; i <= READ_SIZE + 2 && buff[i] != '\0'; i += 1)
        tmp[i] = buff[i];
    for (count = buff_len; count != line_len + buff_len; count += 1)
        tmp[count] = line[count - buff_len];
    for (int i = count; i < line_len + buff_len + 2; i += 1)
        tmp[i] = '\0';
    free(line);
    line = fill_strings(buff, tmp, buff_len);
    free(tmp);
    return (line);
}

static int get_read(char **l_line, int fd, ssize_t size)
{
    char *line = *l_line;
    char *temp = calloc(READ_SIZE + 1, sizeof(char));
    int len = 0;

    line = my_realloc(line, READ_SIZE + 1);
    if (temp == NULL || line == NULL)
        return (-84);
    for (int i = 0; i <= READ_SIZE; i += 1)
        temp[i] = '\0';
    size = read(fd, temp, READ_SIZE);
    if (size == -1 || (size == 0 && line[0] == '\0'))
        return (size);
    for (; line[len] != '\0'; len += 1);
    for (int i = 0; i <= READ_SIZE && temp[i] != '\0'; i += 1) {
        line[len] = temp[i];
        len += 1;
    }
    line[len] = '\0';
    free(temp);
    *l_line = line;
    return (size);
}

char *get_next_line(int fd)
{
    static char *buff;
    char *line = NULL;
    int got_line = 0;
    ssize_t size = 0;

    if (buff == NULL && READ_SIZE > 0) {
        buff = calloc((READ_SIZE + 2), sizeof(char));
        for (int i = 0; buff != NULL && i < READ_SIZE + 2; i += 1)
            buff[i] = '\0';
    }
    while (got_line == 0 && buff != NULL && fd != -1 && READ_SIZE > 0) {
        for (int i = 0; buff[i] && i < READ_SIZE + 2 && got_line == 0; i += 1)
            got_line = (buff[i] == '\n' ? 1 : 0);
        size = (got_line == 0 ? get_read(&line, fd, size) : size);
        if (size == -1 || (size == 0 && buff[0] == '\0') || size == -84)
            return (NULL);
        got_line = (!line || line[0] == '\0' || size < READ_SIZE ? 1 : 0);
        for (int i = 0; line && line[i] && got_line == 0; i += 1)
            got_line = (line[i] == '\n' ? 1 : 0);
    }
    return (fd == -1 || READ_SIZE <= 0 || !buff ? NULL : my_strcat(buff, line));
}
