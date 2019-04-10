#!/bin/bash
gcc syntax.c
gcc syntax.c -o syntax
./syntax $1
rm syntax.exe
rm a.exe

