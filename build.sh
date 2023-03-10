#!/bin/bash

EXEC="main"

MUSL_ROOT=$(find /usr -iname 'musl' -type d -not -path '*/\.*')
MUSL_INC="$MUSL_ROOT/include"
MUSL_LIB="$MUSL_ROOT/lib"
MUSL_BIN="$MUSL_ROOT/bin"
CC="$MUSL_BIN/musl-gcc"
CFLAGS="-Wall -Wpedantic -ggdb -std=c99"
CDEFINES=""
CFILES="main.c"
CLIBS="-lm"

$CC $CFLAGS $CDEFINES $CFILES -o $EXEC $CLIBS
./$EXEC
