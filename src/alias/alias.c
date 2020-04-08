/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** alias
*/

#include "my.h"
#include "mysh.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>

static char ***get_alias(FILE *fd, int nb_line)
{
    int read = 0;
    char *line = NULL;
    unsigned long int len = 0;
    char ***tab = malloc(sizeof(char **) * nb_line);

    if (tab == NULL)
        return (NULL);
    for (int i = 0; i != nb_line; i++)
        tab[i] = NULL;
    for (int i = 0; read != -1;) {
        read = getline(&line, &len, fd);
        if (read > 0 && line != NULL && i < nb_line && line[0] != '\n')
            tab[i++] = split_line(remove_endline(line));
    }
    tab[nb_line - 1] = NULL;
    return (tab);
}

static int get_size(char *fp)
{
    struct stat buf;

    stat(fp, &buf);
    return (buf.st_size);
}

int get_nb_line(char *fp)
{
    int size = get_size(fp);
    int fd = open(fp, O_RDONLY);
    char buffer[size];
    int count = 0;

    if (fd == -1 || size <= 0)
        return (-1);
    read(fd, buffer, size);
    for (int i = 0; i < size; i++)
        if (buffer[i] == '\n')
            count++;
    close(fd);
    return (count + 1);
}

char ***load_alias(int nb_line, char *fp)
{
    FILE *fd = fopen(fp, "r");

    if (fd == NULL || nb_line == 0)
        return (NULL);
    return (get_alias(fd, nb_line));
}
