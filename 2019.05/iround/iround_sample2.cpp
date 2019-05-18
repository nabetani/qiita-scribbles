#include <cmath>
#include <iomanip>
#include <iostream>

constexpr int iround(float v) {
  if (v >= 0) {
    return static_cast<int>(v + 0.5f);
  } else {
    return -static_cast<int>(-v + 0.5f);
  }
}

int main() {
  float src = 0.49999997f;
  auto irounded = iround(src);
  auto lrounded = std::lround(src);
  std::cout << std::fixed << std::setprecision(8) //
            << "iround(" << src << "f) == " << irounded << "\n"
            //=> iround(0.49999997f) == 1
            << "lround(" << src << "f) == " << lrounded << "\n";
            //=> lround(0.49999997f) == 0
}