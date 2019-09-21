// clang++ -Wall -std=c++11
#include "fixfunc.hpp"
#include <functional>
#include <iostream>

struct foo {
  int m[10];
  void operator()() const {
    std::cout << "foo" << std::endl;
    // 略
  }
};

struct bar {
  int m[100];
  void operator()() const {
    std::cout << "bar" << std::endl;
    // 略
  }
};

struct too_large {
  int m[200];
  void operator()() const {
    // 略
  }
};

void fuga() {
  using ft = nabetani::func_type<void(void)>;
  constexpr size_t size = ft::size<foo, bar>();
  nabetani::fixfunc<void(void), size> func = foo{};
  func(); // calls foo::operator()
  func = bar{}; // okay
  func(); // calls bar::operator()
  //func = too_large{}; // compile error
}

int main() {
  fuga();
}
