/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** exec_cmd
*/

#include "mysh.h"
#include "my.h"
#include "parser.h"

static int exec_cmd(char *str, char **env)
{
    char *exec_path = check_command(str, env);
    char **my_argv = str_to_word_array(str, " ");
    int ret_value = 0;

    if (exec_path == NULL)
        return (-2);
    free(str);
    ret_value = execve(exec_path, my_argv, env);
    free_tab(&my_argv);
    free(exec_path);
    return (ret_value);
}

static int call_exec(char *str, char **env, int error)
{
    error = exec_cmd(my_strdup(str), env);
    if (error == -1) {
        if (errno == ENOEXEC)
            fprintf(stderr, "%s: Exec format error. Wrong Architecture.\n",
            my_sprintf("%s%s", "./", str, NULL));
        else if (errno == EACCES)
            fprintf(stderr, "%s: Permission denied.\n", str);
        return (-1);
    }
    if (error == -2) {
        if (str[0] == '!') {
            printf("%s: Event not found.\n", &str[1]);
        } else {
            printf("%s: Command not found.\n", str);
            error = -1;
        }
    }
    return (error);
}

static void run_child(node_t *tree, char **env, int fd_write, int *fds)
{
    tree = get_prev_node(tree);
    if (tree != NULL)
        run_exec(tree, env, fds[1]);
    close(fd_write);
    close(fds[0]);
}

static void run_parent(int *fds, node_t *tree, char **env)
{
    if (fds[1] != 1)
        close(fds[1]);
    if (tree->top && ((tree->top->top && tree->top->right == tree
    && tree->top->top->cmd && tree->top->top->cmd[0] != '|') ||
    (tree->top->left == tree && tree->top->cmd && tree->top->cmd[0] != '|')))
        get_redirection(tree);
    if (call_exec(clean_str(&tree->cmd), env, 0) == -1)
        exit(-1);
}

int run_exec(node_t *tree, char **env, int fd_write)
{
    pid_t pid = -2;
    int fds[2] = {0, 1};

    if ((get_prev_node(tree) != NULL))
        pipe(fds);
    dup2(fds[0], 0);
    dup2(fd_write, 1);
    if (get_prev_node(tree))
        pid = fork();
    if (pid == -1)
        return (-1);
    else if (pid == 0)
        run_child(tree, env, fd_write, fds);
    else
        run_parent(fds, tree, env);
    return (0);
}
