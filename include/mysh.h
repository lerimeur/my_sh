/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** 42sh header
*/

#ifndef MINISHELL_H
#define MINISHELL_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

#define BOLD "\033[1m"
#define FLAT "\033[0m"
#define NORMAL "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAG "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"

#define UNUSED __attribute__((unused))

#ifndef UNIT_TEST
#define STATIC static
#else
#define STATIC
#endif

#define CHAR_IS_NUM(c) (c >= '0' && c <= '9') ? 1 : 0

typedef struct sh_s {
    char ***alias;
    char **env;
    char **var;
    char **pwd;
    char *home;
    char *user;
    char *previous_line;
    int ex;
} sh_t;

typedef struct node_s {
    char *cmd;
    int len;
    struct node_s *top;
    struct node_s *left;
    struct node_s *right;
} node_t;

static int ERROR __attribute__((unused))
= 84;

void run_exit(char *cmd, __attribute__((unused))sh_t *sh);
void run_cd(char *path, sh_t *sh);
void run_env(__attribute__((unused))char *cmd, sh_t *sh);
void run_echo(char *cmd, UNUSED sh_t *sh);
void run_set(char *cmd, UNUSED sh_t *sh);
void run_unset(char *params, sh_t *sh);
void run_alias(char *cmd, sh_t *sh);
void run_unalias(char *params, sh_t *sh);
void run_which(char *cmd, sh_t *sh);
void run_where(char *str, sh_t *sh);
void run_history(char *cmd, sh_t *sh);
char *run_history_seach(char *cmd, sh_t *sh);

char **get_pwd(char **pwd);
void run_setenv(char *params, sh_t *sh);
void run_unsetenv(char *params, sh_t *sh);
int run_exec(node_t *tree, char **env, int fd_read);
void get_cmd(node_t *tree, sh_t *sh);
char *clean_str(char **str);
void error_msg(char *cmd);

bool is_eq_strict(char *str, char *search);
void get_var(char *str, char **vvar, char **vvalue);
void check_child_errors(int status);
int get_redirect(node_t *tree, char **e_env);
char *check_redirect(node_t *tree, int **fd);

node_t *create_tree(char *str, int max_len, sh_t *sh);
void destroy_tree(node_t **tree);
node_t *get_next_node(node_t *node);
void get_redirection(node_t *node);
node_t *get_prev_node(node_t *node);

node_t *go_to_top(node_t *node);
void call_execution(node_t *tree, sh_t *sh);
bool my_strbeg_eq(char *str, char const *cmp);
char *get_cmd_path(char *str, char **env);
char *check_command(char *str, char **env);

char *find_env_value(char *var, char **env, char delim);
int load_env(char **env, sh_t *sh);
bool is_alphanumeric(char *var, char *builtin, bool just_first);
int nb_params(char *str);

void show_local_env(sh_t *sh);
int create_local_env(char ***local_env);

char **split_line(char *line);
char ***load_alias(int nb_line, char *fp);
int get_nb_line(char *fp);

void my_show_tab(char **tab);
void my_show_big_tab(char ***tab);
char *remove_endline(char *str);


void show_alias(sh_t *sh);
void find_alias_value(char ***alias, char *var_to_find);
bool is_in_alias(char ***alias, char *var);
void change_alias_var(char ***alias, char **new_alias);
char ***add_alias_var(char ***alias, char **new_alias);
char ***remove_alias(char ***alias, char *command);

//history && prompt
char *history_key(char *str, int status, sh_t *sh);
int nb_char(char *str, char del);
char **add_env_var(char **env, char *var, char *new_value, char *deli);
void error(sh_t *sh, char *line, int status);
void change_pwd_env(char **env, char oldbuf[]);
char **get_pwd(char **pwd);
void my_swap(char **a, char **b);
void find_command_in_alias(char ***alias, char *cmd,
bool show, int *val);

#endif
