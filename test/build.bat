@echo off

for /F "delims=" %%i in ("%cd%") do @set currdir=%%~nxi

if "%currdir%" == "test" (
set BIN_DIR=
) else (
set BIN_DIR=test\
)

clang -Wall -Wpedantic -ggdb -std=c11 -O2 -mavx2 -march=native %BIN_DIR%test.c -o %BIN_DIR%test.exe

.\%BIN_DIR%test.exe
