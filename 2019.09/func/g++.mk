run : bin/g++-build
	bin/g++-build

gpp := $(shell which g++-9 || which g++-8 || which g++-7 || which g++-6 || which g++-5 || which g++-4)

bin/g++-build : fixfunc.hpp main.cpp clang.mk
	mkdir -p bin
	$(gpp) -std=c++11 -Wall -O3 main.cpp -o bin/g++-build
