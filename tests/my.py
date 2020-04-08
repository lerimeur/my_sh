#!/usr/bin/env python3
##
## EPITECH PROJECT, 2019
## 42sh.
## File description:
## Defines the Test class.
##

from subprocess import Popen, PIPE
import os

class Tests:
    def __init__(self, cmd):
        self.command = str.encode(cmd+"\n")
        self.myenv = os.environ
        self.refenv = os.environ
        self.mysh = Popen([str.encode('./42sh')], stdin=PIPE, stdout=PIPE,
                          stderr=PIPE, shell=True, env=self.myenv)
        self.ref = Popen([str.encode('tcsh')], stdin=PIPE, stdout=PIPE,
                          stderr=PIPE, shell=True, env=self.refenv)
        self.myout, self.myerr = self.mysh.communicate(input = self.command)
        self.refout, self.referr = self.ref.communicate(input = self.command)
        self.myret = self.mysh.returncode
        self.refret = self.ref.returncode

    def newCmd(self, cmd):
        self.command = str.encode(cmd+"\n")
        self.myout, self.myerr = self.mysh.communicate(input = self.command)
        self.refout, self.referr = self.ref.communicate(input = self.command)
        self.myret = self.mysh.returncode
        self.refret = self.ref.returncode

    def test(self):
        assert(self.myout == self.refout)
        assert(self.myerr == self.referr)
        assert(self.myret == self.refret)
        assert(self.myenv == self.refenv)

    def specialOutput(self, output):
        if (os.access(output, os.F_OK | os.R_OK)):
            opFile = open(output, "r")
            opDesired = opFile.read()
            assert(self.myout == opDesired)
        else:
            assert(self.myout == output)
        assert(self.myerr == self.referr)
        assert(self.myret == self.refret)
        assert(self.myenv == self.refenv)
