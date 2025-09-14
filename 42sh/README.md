# 42sh

1. Project Overview

Create a basic fully functionnal shell.

2. Installation Instructions

Clone the project, install the packages automake and autoconf.

3. Usage Guide

Run 'autoreconf --install' in the main directory, then create a directory 'build' and run '../configure'. You can add 'CFLAGS=...' if needed ('CFLAGS=-g' for example). Execute 'make' to compile and then run the '42sh' binary.
A 'make check' rule is available including functionnal test using Criterion and shell scripts to test the whole program.


How to run tests ?

python testsuite.py --binary {path/to/42sh} --tests {path/to/tests}

with a build_test directory for example

How to run gcoverage ?

Compile 42sh with CFLAGS : -fPIC -coverage
Link 42sh with LDFLAGS : -lgcov

And then run : gcovr --html --html-nested --output=report.html or Make  coverage

//TODO faire un make coverage avec ces commandes
//TODO regarder comment ajouter pour tester avec valgrind
//TODO regarder comment gerer les timeout pour eventuellement eviter boucles infinies
//TODO ajouter couleurs a output (pour simon)
//TODO pytest ?.

How to use clang-format python file ?

python tests/apply_format.py --sources src

4. License

A first-year engineering project from EPITA
