/*
** EPITECH PROJECT, 2019
** 42sh.
** File description:
** Header for unit_tests.
*/

#ifndef _UNIT_TESTS_H_
#define _UNIT_TESTS_H_

#include <criterion/criterion.h>
#include <criterion/redirect.h>

static inline void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

#endif /* _UNIT_TESTS_H_ */
