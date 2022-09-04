#!/bin/zsh

set -xe

gcc-11 -Wall -Wextra -pedantic -std=c11 -o main *.c -DFMEMORY_DEBUG
