// main.c
#include <stdio.h>

extern const int apricot; // foo.c に定義があるのでそれを使う
const int banana; // 仮定義→foo.c に定義があるのでそれを使う
//extern const int coconut; // 定義がないのでエラー
const int grape; // 仮定義→どこにも定義がないので 0 になる

int main()
{
  printf( "apricot: %d\n", apricot ); // => 123
  printf( "banana: %d\n", banana ); // => 456
  printf( "grape: %d\n", grape ); // => 0
}
