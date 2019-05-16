// clang++ -std=c++11 -Wall
#include <cstdio>
#include <iostream>
#include <iterator> // std::begin など

// 配列の参照で受けるときはこんな感じ。
template <size_t array_size>
void int_array_receiver(int const (&ary)[array_size]) {
  for (auto i : ary) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

// C言語風に受けるときはこんな感じ。
void c_style(long const *p, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    std::cout << p[i] << " ";
  }
  std::cout << std::endl;
}

// STL風に受けるときはこんな感じ。
void stl_style(char const *begin, char const * end) {
  for( auto p = begin ; p != end ; ++p ){
    std::cout << 0+*p << " ";
  }
  std::cout << std::endl;
}

void func() {
  // 宣言と定義
  int three_integers[] = {1, 2, 3}; // 要素数の指定は省略できる
  long five_longs[5] = {9, 8, 7};   // { 9, 8, 7, 0, 0 } と同じ。
  char hoge[] = "hoge"; // 文字列リテラルで初期化できる。null-terminator
                        // を含むので hogeは5要素
  char fuga[7] = "fuga"; // 末尾の3つはゼロになる。

  // 関数に渡す

  // 配列の参照を渡すとサイズも渡せる
  int_array_receiver(three_integers);

  // C言語風に渡すときはサイズを計算する必要がある
  c_style(five_longs, sizeof(five_longs) / sizeof(*five_longs));

  // STL風に渡すときは std::begin などを使う
  stl_style( std::begin(hoge), std::end(hoge) );

  // range based for が使える
  for (auto c : fuga) {
    std::cout << c + 0 << " ";
  }
  std::cout << std::endl;
}

int main() { func(); }
