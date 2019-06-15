// clang++ -std=c++14 -Wall
#include <iostream>
#include <memory>   // std::unique_ptr

std::unique_ptr<char[]> returns_ptr() {
  auto p = std::make_unique<char[]>(10);
  for (size_t ix = 0; ix < 10; ++ix) {
    p[ix] = ix + 1 == 10 ? 0 : 'a' + ix;
  }
  return p;
}

void func(size_t n) {
  // 宣言と定義 ( make_unique は C++14以降 )
  auto p = std::make_unique<int[]>(n); // n は要素数。初期値を入れる方法はない。
  p[0] = 100;
  p[1] = 101;
  p[2] = 102;
  auto q = std::make_unique<int[]>(0); // サイズ0でもOK
  auto r = std::move(p);               // move できる
  for (auto ix = 0; ix < n; ++ix) {    // range based for は使えない
    std::cout << r[ix] << " ";
  }
  std::cout << std::endl;

  auto s = returns_ptr(); // 返戻値として使える
  std::cout << s.get() << std::endl;
}

int main() { func(3); }