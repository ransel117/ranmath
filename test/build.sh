#!/bin/sh


if [ "`basename $PWD`" != "test" ];
then
BIN_DIR="test/"
else
BIN_DIR=""
fi

gcc -Wall -Wpedantic -ggdb -std=c11 -O2 -mavx2 ${BIN_DIR}test.c -o ${BIN_DIR}test

./${BIN_DIR}test
