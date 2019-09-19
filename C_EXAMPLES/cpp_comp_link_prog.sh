#!/bin/bash
cpp-9 prog.c -o prog_cpp.c
gcc-9 -c -Wall prog_cpp.c -o prog_cpp.o
gcc-9 prog_cpp.o -o prog.exe -lm 
#oppure in un colpo solo: gcc -Wall prog.c -o prog.exe
