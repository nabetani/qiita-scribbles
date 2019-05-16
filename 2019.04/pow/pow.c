// clang -Wall -std=c11 pow.c

#include <stdio.h>

int pow_(int radix, int index);
int one(int unused0,int unused1){  return 1; }

int pow_(int radix, int index) {
  int i = index/2;
  int p = ((int(*[])(int,int)){ one, pow_ })[!!i](radix,i);
  return p*p*(1+(index&1)*(radix-1));
}

int main() {
   int radix = 0;
   int index = 0;
   scanf( "%d %d", &radix, &index );
   printf( "%d\n", pow_(radix,index) );
}