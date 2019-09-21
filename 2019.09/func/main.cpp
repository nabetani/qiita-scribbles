#include <iostream>
#include <functional>
#include <string>
#include "fixfunc.hpp"

using namespace std;

int simple_func( int a, int b )
{
  cout << "in " << __FUNCTION__ << endl;
  return a+b;
}

struct func_with_int_t{
  int m;
  int operator()( int a, int b ) const {
    cout << "in " << __FUNCTION__ << endl;
    return a+b+m;
  }
};

struct func_with_string_t{
  std::string m;
  int operator()( int a, int b ) const {
    cout << "in " << __FUNCTION__ << endl;
    return a+b+m.size();
  }
};


void use_fixfunc()
{
  constexpr size_t size = 100;
  auto caller = []( char const * name, nabetani::fixfunc<int(int,int), size> const & proc ){
    cout << name << ": " << proc( 1, 200 ) << endl;
  };
  caller( "simple", &simple_func );
  caller( "with int", func_with_int_t{123} );
  caller( "with string", func_with_string_t{ "hoge" } );
}

void use_stdfunction()
{
  auto caller = []( char const * name, function<int(int,int)> const & proc ){
    cout << name << ": " << proc( 1, 200 ) << endl;
  };
  caller( "simple", simple_func );
  caller( "with int", func_with_int_t{123} );
  caller( "with string", func_with_string_t{ "hoge" } );
}



int main( int argc, char const * argv[] )
{
  use_fixfunc();
  use_stdfunction();
}
