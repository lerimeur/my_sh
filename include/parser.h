/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** lib header of my_ls
*/

#ifndef PARSER_H
#define PARSER_H
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *get_search(char *str, char *search);
char **add_env_var(char **env, char *var, char *new_value, char *deli);

void change_env_var(char **env, char *var, char *new_value, char *deli);
bool is_in_env(char **env, char *var);
char **remove_env(char **env, char *command, char *deli);

typedef enum cmd_id_s {
    NO = 0,
    AND = 1,
    OR = 2,
    THEN = 3
} cmd_id_t;

typedef struct command_s {
    char *cmd;
    cmd_id_t id;
    struct command_s *next;
} command_t;

int check_alias(char **arg_str, sh_t *sh, char **last_cmd);
command_t *get_separator(char *input);
int check_grammar(char *str, int max_len);
char *replace_in_str(char *str, char *result, int beg, int len);
int get_dollars(char **arg_str, sh_t *sh);
int remove_quotes(char *str);
void init_node(node_t *node, node_t *top, node_t *left, node_t *right);
int check_grammar(char *str, int max_len);
int get_tilde(char **arg_str, sh_t *sh);
int check_alias(char **arg_str, sh_t *sh, char **last_cmd);
int check_cmd_errors(char *str, int len);
int check_errors_matches(char **str, node_t *node,
int max_len, int *len);
int get_node_errors(char **str, int max_len, node_t *node);
int check_cmd_validity(node_t *node, sh_t *sh,
int len, char *str);

bool is_cmd_null(char *cmd);
void edit_status_value(sh_t *sh);
int check_separator(command_t *cmd, sh_t *sh);
void get_end_cmd(node_t **tree, sh_t *sh, char *save_input, int *max);
command_t *init_beg_cmd(char *input, sh_t *sh);
char *check_history_call(char **input, sh_t *sh);
#endif
