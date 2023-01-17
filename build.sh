#!/bin/bash

CC="cc"
EXEC="./build/main"
CFILES="ranmath.c main.c"
CFLAGS="-Wall -Wpedantic -ggdb -std=c99"
CLIBS="-lm"

$CC $CFLAGS $CFILES -o $EXEC $CLIBS
./build/main
