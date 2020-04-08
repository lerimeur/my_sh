#!/usr/bin/env python3
##
## EPITECH PROJECT, 2019
## 42sh.
## File description:
## Functional tests on simple commands
##

from tests import my


def test_SimpleCMD_LS():
    ls = my.Tests("ls")
    ls.test()


def test_SimpleCMD_LS_concatenatedArgs():
    ls_lar = my.Tests("ls -lar")
    ls_lar.test()


def test_SimpleCMD_LS_separatedArgs():
    ls_ls_l_a_r_t = my.Tests("ls -l -a -r -t")
    ls_ls_l_a_r_t.test()


def test_SimpleCMD_LS_Fail():
    ls_fail = my.Tests("ls -e")
    ls_fail.test()


def test_SimpleCMD_exit0():
    exit0 = my.Tests("exit")
    exit0.test()


def test_SimpleCMD_exit9000():
    exit9000 = my.Tests("exit 9000")
    exit9000.test()
