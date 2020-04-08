#!/usr/bin/env python3
##
## EPITECH PROJECT, 2019
## 42sh.
## File description:
## Functional Test on the parser.
##

from tests import my

        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #
        # ~~~ 1 - Too Much Space Tests ~~~ #
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #


def test_PARSER_spaceAtBeginning():
    space = my.Tests("                    ls")
    space.test()


def test_PARSER_spaceAtEnd():
    space = my.Tests("ls                    ")
    space.test()


def test_PARSER_spaceInMiddle():
    space = my.Tests("ls                  -l          -a")
    space.test()


def test_PARSER_spaceEverywhere():
    space = my.Tests("                    ls            -l    -a       ")
    space.test()


        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #
        # ~~~ 2 - Too Much Tabs Tests ~~~ #
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #


def test_PARSER_tabsAtBeginning():
    tabs = my.Tests("\t\t\tls")
    tabs.test()


def test_PARSER_tabsAtEnd():
    tabs = my.Tests("ls\t\t\t\t\t")
    tabs.test()


def test_PARSER_tabsInMiddle():
    tabs = my.Tests("ls\t\t-a\t\t-R")
    tabs.test()


def test_PARSER_tabsEverywhere():
    tabs = my.Tests("\t\tls\t\t\t-l\t-a\t\t\t")
    tabs.test()


        # ~~~~~~~~~~~~~~~~~~~~ #
        # ~~~ 3 - && Tests ~~~ #
        # ~~~~~~~~~~~~~~~~~~~~ #


def test_PARSER_andAtBeginning():
    t_and = my.Tests("&& ls")
    t_and.test()


def test_PARSER_andAtEnd():
    t_and = my.Tests("ls &&")
    t_and.test()


def test_PARSER_andInMiddle():
    t_and = my.Tests("ls && cat ./main/main.c")
    t_and.test()


def test_PARSER_andFirstCmdFails():
    t_and = my.Tests("lol && cat ./main/main.c")
    t_and.test()


def test_PARSER_andSecondCmdFails():
    t_and = my.Tests("ls && cat lol")
    t_and.test()


def test_PARSER_andMultiple():
    t_and = my.Tests("ls && cat ./main/main.c && echo hello world && ls -l \
&& ls -r")
    t_and.test()


def test_PARSER_andMultiple2():
    t_and = my.Tests("ls && && cat ./main/main.c && echo hello world && ls -l \
&& yolo && ls -r")
    t_and.test()


        # ~~~~~~~~~~~~~~~~~~~~ #
        # ~~~ 4 - || Tests ~~~ #
        # ~~~~~~~~~~~~~~~~~~~~ #


def test_PARSER_orAtBeginning():
    t_or = my.Tests("|| ls")
    t_or.test()


def test_PARSER_orAtEnd():
    t_or = my.Tests("ls ||")
    t_or.test()


def test_PARSER_orInMiddle():
    t_or = my.Tests("ls || cat ./main/main.c")
    t_or.test()


def test_PARSER_orFirstCmdFails():
    t_or = my.Tests("lol || cat ./main/main.c")
    t_or.test()


def test_PARSER_orSecondCmdFails():
    t_or = my.Tests("ls || cat lol")
    t_or.test()


def test_PARSER_orMultiple():
    t_or = my.Tests("ls || cat ./main/main.c || echo hello world || ls -l \
|| ls -r")
    t_or.test()


def test_PARSER_orMultiple2():
    t_or = my.Tests("lol || car ./main/main.c || yolo || ls -r")
    t_or.test()


def test_PARSER_orMultiple3():
    t_or = my.Tests("lol || car ./main/main.c || || yolo || ls -r")
    t_or.test()


        # ~~~~~~~~~~~~~~~~~~~ #
        # ~~~ 5 - ; Tests ~~~ #
        # ~~~~~~~~~~~~~~~~~~~ #


def test_PARSER_semicolonAtBeginning():
    t_semicolon = my.Tests("; ls")
    t_semicolon.test()


def test_PARSER_semicolonAtEnd():
    t_semicolon = my.Tests("ls ;")
    t_semicolon.test()


def test_PARSER_semicolonInMiddle():
    t_semicolon = my.Tests("ls ; cat ./main/main.c")
    t_semicolon.test()


def test_PARSER_semicolonFirstCmdFails():
    t_semicolon = my.Tests("yolo ; cat ./main/main.c")
    t_semicolon.test()


def test_PARSER_semicolonSecondCmdFails():
    t_semicolon = my.Tests("ls ; cat lol")
    t_semicolon.test()


def test_PARSER_semicolonMultiple():
    t_semicolon = my.Tests("ls ; cat ./main/main.c ; echo hello world ; ls -l ; ls -r")
    t_semicolon.test()


def test_PARSER_semicolonMultiple2():
    t_semicolon = my.Tests("lol ; car ./main/main.c ; yolo ; ls -r ;")
    t_semicolon.test()


def test_PARSER_semicolonMultiple3():
    t_semicolon = my.Tests(";;;;;lol ; car ./main/main.c ;;;; yolo ; \
ls -r;;;echo hello world;")
    t_semicolon.test()


        # ~~~~~~~~~~~~~~~~~~~ #
        # ~~~ 6 - | Tests ~~~ #
        # ~~~~~~~~~~~~~~~~~~~ #


def test_PARSER_pipeAtBeginning():
    t_pipe = my.Tests("| echo hello world")
    t_pipe.test()


def test_PARSER_pipeAtEnd():
    t_pipe = my.Tests("ls |")
    t_pipe.test()


def test_PARSER_pipeInMiddle():
    t_pipe = my.Tests("echo hello world | cat")
    t_pipe.test()


def test_PARSER_pipeFirstCmdFails():
    t_pipe = my.Tests("yolo | cat")
    t_pipe.test()


def test_PARSER_pipeSecondCmdFails():
    t_pipe = my.Tests("ls | lol")
    t_pipe.test()


def test_PARSER_pipeMultiple():
    t_pipe = my.Tests("cat ./main/main.c | cat | ./42sh")
    t_pipe.test()


def test_PARSER_pipeMultiple2():
    t_pipe = my.Tests("cat ./main/main.c | cat |")
    t_pipe.test()


def test_PARSER_pipe_LoicTesMort():
    t_pipe = my.Tests("ls | cat -e | cat -e | cat -e | cat -e | cat -e | cat \
-e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | \
cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e \
| cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat \
-e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | \
cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e \
| cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat \
-e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | \
cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e \
| cat -e | cat -e | cat -e | cat -e")
    t_pipe.test()


        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #
        # ~~~ 7 - Redirections Tests ~~~ #
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #

# SL = < | DL = << | SR = > | DR = >>


def test_PARSER_redirSL_Beginning():
    redir = my.Tests("< echo hello world")
    redir.test()


def test_PARSER_redirSL_End():
    redir = my.Tests("ls <")
    redir.test()


def test_PARSER_redirSL_InMiddle():
    redir = my.Tests("echo hello world > lol ; cat lol ; rm lol")
    redir.test()


def test_PARSER_redirDL_Beginning():
    redir = my.Tests("<< echo hello world")
    redir.test()


def test_PARSER_redirDL_End():
    redir = my.Tests("ls <<")
    redir.test()


def test_PARSER_redirDL_InMiddle():
    redir = my.Tests("echo hello world >> lol ; cat lol ; rm lol")
    redir.test()


def test_PARSER_redirSR_Beginning():
    redir = my.Tests("> echo hello world")
    redir.test()


def test_PARSER_redirSR_End():
    redir = my.Tests("ls >")
    redir.test()


def test_PARSER_redirSR_InMiddle():
    redir = my.Tests("cat < lol")
    redir.test()


def test_PARSER_redirDR_Beginning():
    redir = my.Tests(">> echo hello world")
    redir.test()


def test_PARSER_redirDR_End():
    redir = my.Tests("ls >>")
    redir.test()


        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #
        # ~~~ 8 - Everything Tests ~~~ #
   # ~~ # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #~~~~ #
   # ~~ Loïc si tu survies ça, t'es fort. ~~ #
   # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #


def test_PARSER_typoMistake1():
    typo = my.Tests("echo lol >>> lol")
    typo.test()


def test_PARSER_typeMistake2():
    typo = my.Tests(";ls\t-la | cat;")
    typo.test()


def test_PARSER_drunkenInput1():
    drunk = my.Tests("      ;;;; ls -l | cat ;;\t\t ls-e\nls -e\necho hello \
world")
    drunk.test()


def test_PARSER_complexCmd_MiniShell2Subject():
    subject = my.Tests("mkdir test ; cd test ; ls -a ; ls | cat | wc -c > \
tutu ; cat tutu ; rm -rfd test")
    subject.test()


def test_PARSER_complexCmd_42shSubject():
    subject = my.Tests("cd ; </etc/hosts od -c | grep xx | wc >> /tmp/z -l ; \
cd - && echo “OK”")
    subject.test()


def test_PARSER_complexCmd1():
    cplxCmd = my.Tests("echo \"hello       world\" | cat > lol ; cat lol ; \
echo \"how are y\t\tyou doing??      \" >> lol ; cat lol ;; rm lol && ls")
    cplxCmd.test()


def test_PARSER_complexCmd2():
    cplxCmd = my.Tests("")
    cplxCmd.test()
