run : bin/clangbuild
	bin/clangbuild

bin/clangbuild : fixfunc.hpp main.cpp clang.mk
	mkdir -p bin
	clang++ -std=c++11 -Wall -O3 main.cpp -o bin/clangbuild
