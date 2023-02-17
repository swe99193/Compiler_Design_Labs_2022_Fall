#!/bin/bash

bison -d parser.y
flex scanner.l
gcc -Wall -std=c11 -D_POSIX_C_SOURCE=1 -o parser parser.tab.c lex.yy.c -lfl
