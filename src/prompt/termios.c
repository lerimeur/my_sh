/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** prompt
*/

#include "prompt.h"
#include <string.h>

static int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i]) {
        i++;
    }
    return (s1[i] - s2[i]);
}

int reset_term(termios_t *term)
{
    if (tcsetattr(0, TCSANOW, term) == -1)
        return (-1);
    free(term);
    return (0);
}

void my_memcpy(void *dest, void *src, size_t size)
{
    char *tsed = (char *)dest;
    char *crs = (char *)src;

    for (size_t i = 0; i < size; i++)
        tsed[i] = crs[i];
}

char *my_getenv(char *var, char **env)
{
    char *envar;

    for (int i = 0; env[i]; i++) {
        if (my_strncmp(env[i], var, 5) == 0) {
            envar = env[i];
            return (&envar[5 + 1]);
        }
    }
    return (NULL);
}

termios_t *get_termios(char **env)
{
    termios_t *term = malloc(sizeof(termios_t));
    termios_t *base_term = malloc(sizeof(termios_t));
    char *term_env = my_getenv("TERM=", env);

    if (!term_env || strlen(term_env) == 0)
        return (NULL);
    tcgetattr(0, base_term);
    my_memcpy(term, base_term, sizeof(termios_t));
    tgetent(NULL, term_env);
    term->c_lflag &= ~(ICANON);
    term->c_lflag &= ~(ECHO);
    term->c_cc[VMIN] = 1;
    term->c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSADRAIN, term) == -1)
        return (NULL);
    free(term);
    return (base_term);
}
