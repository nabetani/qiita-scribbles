#include <iostream>

float const float_const = 1.0;
int const int_const = 1;


int main()
{
  enum{
    foo = (int)float_const,
    bar = int_const,
  };
  std::cout << foo << " " << bar << std::endl;
}
