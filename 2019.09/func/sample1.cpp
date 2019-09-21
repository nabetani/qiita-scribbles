// clang++ -Wall -std=c++11
#include <functional>
#include <iostream>

struct foo {
  int m[10];
  void operator()() const {
    // 略
  }
};

struct bar {
  int m[100];
  void operator()() const {
    // 略
  }
};

void hoge() {
  std::function<void()> func; // 何が入るのかわからない。
  func = foo{};               // sizeof(foo) の分のメモリ確保が必要
  func = bar{}; // sizeof(foo)<sizeof(bar) なので、メモリの確保と開放が必要。
}

void fuga() {}

int main() {
  hoge();
  fuga();
}
