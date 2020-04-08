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
#include "history.h"

char *go_in_history(sh_t *sh, int way, char **line, int *index_line)
{
    char *str = history_key(NULL, way, sh);

    if (str == NULL)
        return (*line);
    for (int i = 0; str[i]; i++)
        if (str[i] == '\n')
            str[i] = '\0';
    erase_line(sh, line, index_line, 1);
    free(*line);
    *line = NULL;
    *line = strdup(str);
    my_putchar_0('\r');
    print_prompt(sh);
    my_putstr_0(*line);
    *index_line = my_strlen(*line);
    return (*line);
}

char *handle_special_key(sh_t *sh, char **line, char buff[10], int *index)
{
    if (buff[0] == 10)
        handle_return(sh, line, index);
    if (buff[0] == 127)
        handle_backspace(sh, *line, index);
    if (buff[0] == 12)
        do_clear(sh, line);
    if (buff[0] == 4)
        return (handle_eof(sh, line));
    if (buff[0] == 27)
        handle_arrows(sh, buff, line, index);
    if (buff[0] == 21)
        erase_line(sh, line, index, 2);
    if (buff[0] == 1)
        do_ctrl_a(index);
    if (buff[0] == 5)
        do_ctrl_e(sh, line, index);
    if (buff[0] == 9)
        do_tab(sh, line, index);
    return (*line);
}

void run_prompt(sh_t *sh, char *line)
{
    char buff[10];
    int size_read;
    int index = 0;

    print_prompt(sh);
    while (1) {
        size_read = read(0, buff, 9);
        buff[size_read] = '\0';
        if (is_printable(buff[0]))
            line = print_key(sh, line, buff, &index);
        else
            line = handle_special_key(sh, &line, buff, &index);
        if (line == NULL) {
            free(line);
            my_putstr_0("exit\n");
            return;
        }
    }
}

void run_minishell(sh_t *sh, termios_t *base_term)
{
    char *line = calloc(2, sizeof(char));

    get_sh_var(1, sh);
    if (base_term == NULL)
        empty_env_prompt(sh);
    signal(SIGINT, inthandler);
    if (line == NULL)
        exit(84);
    run_prompt(sh, line);
}