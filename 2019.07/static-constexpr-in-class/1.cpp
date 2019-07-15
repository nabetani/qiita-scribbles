// -std=c++11 -Wall
#include <iostream>

template <typename type> void foo(type const &v) {
  std::cout << v << std::endl;
}

template <typename type> struct bar { constexpr static type value = 123; };

int main() {
  foo(bar<int>::value); // Undefined symbols(略) "bar::value"
  return 0;
}
