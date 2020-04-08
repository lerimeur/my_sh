/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** redirections hub
*/

#include "mysh.h"
#include "parser.h"
#include "my.h"
#include "get_next_line.h"

static void set_redirection(char *filepath, bool append,
int redirect_fd, bool is_trunc)
{
    int fd = 0;
    int flag = (redirect_fd == 0 ? O_RDONLY : O_RDWR);

    if (redirect_fd != 0)
        flag = flag | O_CREAT;
    if (append)
        flag = O_APPEND | flag;
    else if (is_trunc)
        flag = flag | O_TRUNC;
    fd = open(filepath, flag, 0644);
    if (fd == -1) {
        write(1, filepath, my_strlen(filepath));
        write(1, ": No such file or directory.\n", 29);
        exit(-1);
    }
    dup2(fd, redirect_fd);
    close(fd);
}

static char **realloc_std(char **tab, char *new_value)
{
    int len = 0;
    char **new = NULL;

    if (tab != NULL)
        for (; tab[len] != NULL; len += 1);
    new = calloc((len + 2), sizeof(char *));
    for (int i = 0; i < len + 2; i += 1)
        new[i] = NULL;
    for (int i = 0; i < len; i += 1) {
        new[i] = my_strdup(tab[i]);
        free(tab[i]);
    }
    new[len] = my_strdup(new_value);
    if (tab != NULL)
        free(tab);
    return (new);
}

static void write_all(char **tab, int *fd)
{
    if (tab == NULL || *tab == NULL)
        return;
    for (int i = 0; tab[i] != NULL; i += 1) {
        write(fd[1], tab[i], my_strlen(tab[i]));
        write(fd[1], "\n", 1);
    }
    close(fd[1]);
    dup2(fd[0], 0);
}

static void redirect_in(char *cmd)
{
    char *buffer = NULL;
    char **tab = NULL;
    int fd[2];

    pipe(fd);
    do {
        if (buffer != NULL) {
            free(buffer);
            buffer = NULL;
        }
        buffer = get_next_line(0);
        if (buffer == NULL || buffer[0] == '\0')
            break;
        if (my_strcmp(buffer, cmd) == 0)
            break;
        else
            tab = realloc_std(tab, buffer);
    } while (buffer != NULL);
    write_all(tab, fd);
}

void get_redirection(node_t *node)
{
    char *flags[] = {">", ">>", "<", "<<", NULL};
    bool append[] = {false, true, false, true};
    int fds[] = {1, 1, 0, 0};
    bool is_trunc[] = {true, false, false, false};
    int i = 0;

    if (node->top == NULL || node->top->right == NULL)
        return;
    if (node->top->cmd[0] == '|' && node->top->top != NULL &&
    node->top->top->cmd[0] != '|' && node->top->top->top == NULL)
        node = node->top;
    for (i = 0; flags[i] &&
    my_strcmp(node->top->cmd, flags[i]) != 0; i += 1);
    if (!flags[i] || (node->top->cmd[0] != flags[i][0]))
        return;
    while (flags[i] && my_strlen(flags[i]) != my_strlen(node->top->cmd))
        i += 1;
    if (i == 3)
        redirect_in(node->top->right->cmd);
    else
        set_redirection(node->top->right->cmd, append[i], fds[i], is_trunc[i]);
}
