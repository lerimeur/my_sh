/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Header for {main.c}.
*/

#ifndef _MAIN_H_
#define _MAIN_H_

#ifdef UNIT_TEST
#define LOAD_ALIAS load_alias(get_nb_line("tests/ut/.t_42shrc") + 1, \
"tests/ut/.t_42shrc")
#else
#define LOAD_ALIAS load_alias(get_nb_line(alias_path) + 1, alias_path)
#endif /* UNIT_TESTS */

#endif /* _MAIN_H_ */
