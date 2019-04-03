#include <iostream>
#include <array>

struct foo {
  char const *name;
  void bar(int x) { std::cout << name << " bar: " << x << std::endl; }
  void baz(int x) { std::cout << name << " baz: " << x << std::endl; }
};

void sample() {
  foo abc{ "abc" };
  foo def{ "def" };
  auto mbar = &foo::bar;
  auto mbaz = &foo::baz;
  (abc.*mbar)( 123 ); //=> 「abc bar: 123」を出力
  (def.*mbaz)( 456 ); //=> 「def baz: 456」と出力
}

void sizes()
{
  auto mbar = &foo::bar;
  std::cout << sizeof(mbar) << std::endl;
}

void to_ary(){
  auto mbar = &foo::bar;
  auto old = std::cout.flags();
  auto ary = *reinterpret_cast<std::array<size_t, 2>*>(&mbar);
  std::cout << std::hex << ary[0] << ":" << ary[1] << std::endl;
  std::cout.flags(old);
}

void call(){
  auto mbar = &foo::bar;
  auto ary = *reinterpret_cast<std::array<size_t, 2>*>(&mbar);
  typedef void(func_t)(foo*,int);
  auto func = reinterpret_cast<func_t*>( ary[0] );
  auto f = foo{"hoge"};
  func(&f,789);
}

int main(int argc, char const *argv[]) {
  sample();
  sizes();
  to_ary();
  call();
}
