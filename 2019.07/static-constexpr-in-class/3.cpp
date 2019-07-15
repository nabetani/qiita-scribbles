// -std=c++17 -Wall
#include <iostream>

template <typename type> void foo(type const &v) {
  std::cout << v << std::endl;
}

template <typename type>
struct bar
{
  inline constexpr static type value = 123;
};

int main() {
  foo(bar<int>::value);
  return 0;
}
