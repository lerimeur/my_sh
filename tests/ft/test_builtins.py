#!/usr/bin/env python3
##
## EPITECH PROJECT, 2019
## 42sh.
## File description:
## Functional Test on the builtins.
##

from tests import my

        # ~~~~~~~~~~~~~~~~~~~ #
        # ~~~ Where Tests ~~~ #
        # ~~~~~~~~~~~~~~~~~~~ #

def test_BUILTINS_Where_PWD():
    where = my.Tests("where pwd")
    where.test()


def test_BUILTINS_Where_EMACS():
    where = my.Tests("where emacs")
    where.test()


def test_BUILTINS_Where_LL():
    where = my.Tests("where ll")
    where.specialOutput(b'll is aliased to ls -la\n')


def test_BUILTINS_Where_invalidCmd():
    where = my.Tests("where lol")
    where.test()


        # ~~~~~~~~~~~~~~~~~~~ #
        # ~~~ Which Tests ~~~ #
        # ~~~~~~~~~~~~~~~~~~~ #

def test_BUILTINS_Which_PWD():
    which = my.Tests("which pwd")
    which.test()


def test_BUILTINS_Which_EMACS():
    which = my.Tests("which emacs")
    which.test()


def test_BUILTINS_Which_LL():
    which = my.Tests("which ll")
    which.specialOutput(b'll:\taliased to ls -la\n')


def test_BUILTINS_Which_invalidCmd():
    which = my.Tests("which lol")
    which.test()


        # ~~~~~~~~~~~~~~~~~~ #
        # ~~~ Echo Tests ~~~ #
        # ~~~~~~~~~~~~~~~~~~ #

def test_BUILTINS_Echo_Empty():
    echo = my.Tests("echo")
    echo.test()


def test_BUILTINS_Echo_Basic():
    echo = my.Tests("echo hello world")
    echo.test()

def test_BUILTINS_Echo_weirdChars():
    echo = my.Tests("echo \thello\t                 world\t\t\t")
    echo.test()
