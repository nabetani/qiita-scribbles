#include <iostream>
#include <iomanip>
#include <cmath>

constexpr int iround(float v)
{
  if(v >= 0) {
    return static_cast<int>(v + 0.5f);
  } else {
    return -static_cast<int>(-v + 0.5f);
  }
}

int main()
{
  float src = 8388609.00f;
  auto irounded = iround(src);
  auto lrounded = std::lround(src);
  std::cout 
  << std::fixed 
  << std::setprecision(2)
  << "iround(" << src << "f) == " << irounded << "\n"
  // iround(8388609.00f) == 8388610
  << "lround(" << src << "f) == " << lrounded << "\n";
  // lround(8388609.00f) == 8388609
}