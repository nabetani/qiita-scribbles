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
  std::cout
    << std::setprecision(2)
    << std::fixed;
  for( int p=0 ; p<31 ; ++p ){
    for( int d=-10 ; d<=10 ; ++d ){
      float src = static_cast<float>(1<<p) + static_cast<float>(d*0.5);
      double dsrc = src;
      double dr = std::round(dsrc);
      int ir = iround(src);
      if (ir == dr){
        continue;
      }
      std::cout
        << dsrc
        << " " 
        << dr 
        << " " 
        << ir 
        << "\n";
    }
  }
}