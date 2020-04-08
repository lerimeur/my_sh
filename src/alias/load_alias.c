/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** load_alias
*/

#include "my.h"
#include "mysh.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>

static char *get_var_name(char *line)
{
    int counter = 0;
    char *var = NULL;

    for (int i = 0; line[i]; i++)
        if (line[i] != ' ')
            counter++;
        else
            break;
    var = malloc(sizeof(char) * counter + 1);
    for (int i = 0; i != counter; i++)
        var[i] = line[i];
    var[counter] = '\0';
    return (var);
}

static char *get_var_value(char *line)
{
    int counter = 0;
    char *var = NULL;

    for (int i = 0; line[i]; i++)
        if (line[i] != ' ')
            counter++;
        else
            break;
    var = my_strdup(&line[counter + 1]);
    return (var);
}

char **split_line(char *line)
{
    char **index = malloc(sizeof(char *) * 3);

    index[0] = get_var_name(line);
    index[1] = get_var_value(line);
    index[2] = NULL;
    return (index);
}
