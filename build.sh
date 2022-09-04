#!/bin/zsh

set -xe

gcc-11 -Wall -Wextra -pedantic -std=c11 -o main main.c fmemory.c
