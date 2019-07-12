#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdint>

template< typename t >
void dump( char const * name, t * v )
{
  auto p = reinterpret_cast<std::uint8_t const *>(v);
  std::cout << name << "=";
  for( auto it = p ; it != p+sizeof(*v) ; ++it ){
    std::printf( "%02x ", *it );
  }
  std::cout << "\n";
}

int main()
{
  float f = std::cos( 3.45f );
  double d = std::cos( 3.45 );
  std::cout << "f=" << f << "  d=" << d << std::endl;
  std::printf( "f=%g  d=%g\n", f, d );
  dump("f", &f);
  dump("d", &d);
  return 0;
}
