// -std=c++11 -Wall
#include <iostream>

template <typename type> void foo(type const &v) {
  std::cout << v << std::endl;
}

template <typename type>
struct bar
{
  constexpr static type value = 123;
};

int main() {
  foo(bar<int>::value + 0); // 無駄に0を足すとアドレスを取らなくなる
  return 0;
}
