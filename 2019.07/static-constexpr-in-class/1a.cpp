// -std=c++11 -O3 -Wall
#include <iostream>

template <typename type> 
void foo(type const &v) {
  std::cout << v << std::endl;
}

template <typename type>
struct bar
{
  constexpr static type value = 123;
};

int main() {
  foo(bar<int>::value); // g++-9 では通る。
  return 0;
}
