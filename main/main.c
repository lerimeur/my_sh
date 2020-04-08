/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** main function of 42sh
*/

#include "my.h"
#include "mysh.h"
#include "prompt.h"
#include "main.h"

void no_tty_prompt(sh_t *sh)
{
    char *line = NULL;
    size_t size = 100;

    while (42) {
        if (getline(&line, &size, stdin) == -1 || line == NULL) {
            write(0, "exit\n", 5);
            exit(sh->ex);
        }
        else if (line[0] != '\0') {
            line = remove_endline(line);
            if (line == NULL)
                continue;
            call_cmd(line, sh);
        }
    }
}

static void load_shell_variable(sh_t *sh, char **env)
{
    char *pth = NULL;
    char *alias_path = my_sprintf("%s/%s",
    find_env_value("HOME", env, '='), ".42shrc", NULL);

    load_env(env, sh);
    sh->previous_line = "\0";
    sh->pwd = get_pwd(sh->pwd);
    sh->alias = LOAD_ALIAS;
    free(alias_path);
    sh->home = find_env_value("HOME", sh->env, '=');
    sh->user = find_env_value("USER", sh->env, '=');
    sh->ex = 0;
    create_local_env(&sh->var);
    pth = find_env_value("PATH", sh->env, '=');
    if (sh->home != NULL)
        sh->var = add_env_var(sh->var, "home", sh->home, "\t");
    sh->var = add_env_var(sh->var, "path", (pth == NULL ? "/bin" : pth), "\t");
    sh->var = add_env_var(sh->var, "status", "0", "\t");
}

int main(int argc, char **argv UNUSED, char **env)
{
    sh_t *sh = malloc(sizeof(sh_t));
    termios_t *base_term;

    if (argc != 1)
        return (84);
    load_shell_variable(sh, env);
    if (!isatty(0)) {
        no_tty_prompt(sh);
        return (0);
    }
    base_term = get_termios(sh->env);
    run_minishell(sh, base_term);
    reset_term(base_term);
    return (0);
}
