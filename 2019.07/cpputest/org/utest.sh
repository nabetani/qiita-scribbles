#!/bin/bash

gcc -c ../func.c
g++ -c utest_func.c
g++ -o utest.out func.o utest_func.o -lCppUTest
