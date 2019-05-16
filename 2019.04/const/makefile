all : hoge_clang hoge_gcc

hoge_clang : foo.c main.c
	clang -Wall -std=c99 foo.c main.c -o hoge_clang

hoge_gcc : foo.c main.c
	 gcc-8 -Wall -std=c99 foo.c main.c -o hoge_gcc