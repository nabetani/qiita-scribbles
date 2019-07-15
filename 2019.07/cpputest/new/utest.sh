#!/bin/bash

g++ -Wall -c utest_func.cpp
gcc -Wall -c -I.. backdoor.c
g++ -Wall -o utest.out utest_func.o backdoor.o -lCppUTest
./utest.out
