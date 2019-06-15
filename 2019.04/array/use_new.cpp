// clang++ -std=c++14 -Wall
#include <iostream>
#include <memory> // std::unique_ptr

std::unique_ptr<char[]> returns_ptr() {
  auto p = std::make_unique<char[]>(10);
  for (size_t ix = 0; ix < 10; ++ix) {
    p[ix] = ix + 1 == 10 ? 0 : 'a' + ix;
  }
  return p;
}

void func(size_t n) {
  // make_unique は C++14以降
  // n は要素数。
  // make_unique だとデフォルトコンストラクタが呼ばれる( int なら 0 になる)
  auto p0 = std::make_unique<int[]>(n);

  auto q = std::make_unique<int[]>(0); // サイズ0でもOK

  // unique_ptr + new なら初期値を入れられる。要素数は省略不能。
  auto p1 = std::unique_ptr<int[]>(new int[3]{11, 22, 33});

  // unique_ptr + new なら初期化を回避することもできる。
  auto p2 = std::unique_ptr<int[]>(new int[3]);
  for (size_t ix = 0; ix < 3; ++ix) { // range based for は使えない
    std::cout << p2[ix] << " ";       // 不定の値が出力される
  }
  std::cout << std::endl;

  auto r = std::move(p0);             // move できる
  for (size_t ix = 0; ix < n; ++ix) { // range based for は使えない
    std::cout << r[ix] << " ";
  }
  std::cout << std::endl;

  auto s = returns_ptr(); // 返戻値として使える
  std::cout << s.get() << std::endl;
}

int main() { func(3); }