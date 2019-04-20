// clang++ -std=c++11 -Wall
#include <array>
#include <cstdio>
#include <iostream>

template< typename ary_type >
void ref_receive(ary_type const &ary) {
  for (auto i : ary) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

void copy_receive(std::array<int, 3> ary) {
  for (auto &i : ary) {
    i += 10;
  }
  ref_receive( ary );
}

std::array<int,4> returns_ary(){
  return { 9, 8, 7, 6 };
}

void func() {
  // 宣言と定義
  std::array<int, 3> three_integers = {1, 2, 3}; // 要素数の指定は省略できない
  std::array<long, 5> five_longs = {9, 8, 7}; // { 9, 8, 7, 0, 0 } と同じ。
  std::array<char, 5> hoge = {"hoge"}; // 文字列リテラルで初期化できる
  std::array<char, 7> fuga = {"fuga"}; // 末尾の3つはゼロになる。

  // 複製
  auto foo = three_integers; // コンストラクタで複製できる
  decltype(three_integers) bar;
  bar = foo; // 代入演算子でコピーできる

  // 非参照で渡せばコピーされる( 関数内から bar を変更できない )
  copy_receive(bar);

  // 参照で渡せばコピーされない
  ref_receive(bar);

  // 関数の返戻値としても使える
  auto baz = returns_ary();
  ref_receive(baz);
}

int main() { func(); }
