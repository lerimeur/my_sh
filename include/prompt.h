/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** prompt
*/

#ifndef PROMPT_H
#define PROMPT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include "mysh.h"
#include <termios.h>
#include <term.h>
#include <ncurses.h>


typedef struct termios termios_t;

sh_t *get_sh_var(int mode, sh_t *sh);

void run_minishell(sh_t *sh, termios_t *base_term);
void my_putchar_0(char c);
void my_putstr_0(char *str);
char *my_revstr(char *str);
void inthandler(int sg);
void print_prompt(sh_t *sh);

termios_t *get_termios(char **env);
int reset_term(termios_t *term);
void my_memcpy(void *dest, void *src, size_t size);
char *my_getenv(char *var, char **env);
int is_printable(char c);
char *my_realloc(char *str, int size_to_add);
void erase_line(sh_t *sh, char **line, int *index, int mode);
char *go_in_history(sh_t *sh, int way, char **line, int *index_line);

// Key comb
char *handle_return(sh_t *sh, char **line, int *index);
char *handle_backspace(sh_t *sh, char *line, int *index);
void do_ctrl_a(int *index);
void do_ctrl_e(sh_t *sh, char **line, int *index);
char *handle_eof(sh_t *sh, char **line);
void do_clear(sh_t *sh, char **line);
void handle_arrows(sh_t *sh, char buff[10], char **line, int *index);
int line_is_empty(char *line);
void call_cmd(char *input, sh_t *sh);
void inthandler_empty_env(int sg);

#ifdef UNIT_TEST
#define ISATTY_0 (1)
#else
#define ISATTY_0 (isatty(0) == 1)
#endif /* UNIT_TEST */

void auto_complete_path(char **filename);
int is_filepath(char *str);
void call_globbing(char **line);
int print_key_in_middle(sh_t *sh, char **line, int *index, char buff[10]);
char *print_key(sh_t *sh, char *line, char buff[10], int *index);
void empty_env_prompt(sh_t *sh);
int is_filepath(char *str);
int file_match(char *s1, char *s2);
void call_exit(char *line, int ex);
void do_tab(sh_t *sh, char **line, int *index);

#endif
