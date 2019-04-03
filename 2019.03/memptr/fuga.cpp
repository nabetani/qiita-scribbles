#include <cstddef>
#include <ctime>
#include <iostream>

int main(int argc, char const *argv[]) {
  auto ptr_to_member = &tm::tm_min;
  std::cout << *reinterpret_cast<size_t *>(&ptr_to_member) << ", "
            << offsetof(tm, tm_min) << std::endl;

  return 0;
}
