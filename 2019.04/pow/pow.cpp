// clang++ -Wall -std=c++17 pow.cpp
#include <iostream>
#include <functional>
#include <array>

int pow_(int radix, int index) {
  auto i = index/2;
  auto p = std::array<std::function<int()>,2>{
    [](){return 1;},  
    [&](){return pow_(radix,i);}
  }[!!i]();
  return p*p*std::array<int,2>{1,radix}[index&1];
}

int main() {
   int radix;
   int index;
   std::cin >> radix >> index;
   std::cout << pow_(radix, index) << std::endl;
}