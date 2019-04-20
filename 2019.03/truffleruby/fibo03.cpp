#include <iostream>
#include <stdint.h>
#include <cstdlib>

typedef int64_t num_t;
num_t fibo( int n ){
  if ( n<=1 ){
    return 1;
  } else {
    return fibo(n-1)+fibo(n-2);
  }
}

int main( int argc, char const * argv[]){
  int n = argc<2 ? 1 : std::atoi(argv[1]);
  std::cout << fibo(n) << std::endl;
}
