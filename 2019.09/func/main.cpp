#include "fixfunc.hpp"
#include <functional>
#include <iostream>
#include <string>

using namespace std;

int simple_func(int a, int b) {
  cout << "in " << __FUNCTION__ << endl;
  return a + b;
}

struct func_with_int_t {
  int m;
  int operator()(int a, int b) const {
    cout << "in " << __FUNCTION__ << endl;
    return a + b + m;
  }
};

struct func_with_four_ints_t {
  int m, n, o, p;
  int operator()(int a, int b) const {
    cout << "in " << __FUNCTION__ << endl;
    return a + b + m;
  }
};

struct func_with_many_ints_t {
  std::array<int, 100> m = {};
  int operator()(int a, int b) const {
    cout << "in " << __FUNCTION__ << endl;
    return a + b + m[0];
  }
};

struct func_with_string_t {
  explicit func_with_string_t(char const *s) : m(s) {
    cout << "ctor of func_with_string_t" << endl;
  }
  func_with_string_t(func_with_string_t const &that) : m(that.m) {
    cout << "copy-ctor of func_with_string_t" << endl;
  }
  ~func_with_string_t() { cout << "dtor of func_with_string_t" << endl; }
  std::string m;
  int operator()(int a, int b) const {
    cout << "in " << __FUNCTION__ << endl;
    return a + b + m.size();
  }
};

struct func_with_sideeffect_t {
  func_with_sideeffect_t() : m_{0} {}
  int m_;
  int operator()(int a, int b) {
    cout << "in " << __FUNCTION__ << endl;
    m_ += a + b;
    return a + b + m_;
  }
};

void use_fixfunc() {
  constexpr size_t size = 100;
  auto caller = [](char const *name,
                   nabetani::fixfunc<int(int, int), size> const &proc) {
    cout << name << ": " << proc(1, 200) << endl;
  };
  // caller("simple func", simple_func);
  caller("simple func ptr", &simple_func);
  caller("with int", func_with_int_t{123});
  caller("with string", func_with_string_t{"hoge"});
  nabetani::fixfunc<int(int, int), size> f(func_with_sideeffect_t{});
  cout << "with size effect: " << f(1, 200) << endl;
}

void use_stdfunction() {
  auto caller = [](char const *name, function<int(int, int)> const &proc) {
    cout << name << ": " << proc(1, 200) << endl;
  };
  // caller("simple func", simple_func);
  caller("simple func ptr", &simple_func);
  caller("with int", func_with_int_t{123});
  caller("with string", func_with_string_t{"hoge"});
  caller("with side effect", func_with_sideeffect_t{});

  function<int(int, int)> f(func_with_sideeffect_t{});
  cout << "with size effect: " << f(1, 200) << endl;
}

void calc_size() {
  using ft = nabetani::func_type<int(int, int)>;
  constexpr size_t size0a = ft::size<decltype(simple_func)>();
  constexpr size_t size0b = ft::size<decltype(simple_func) *>();
  constexpr size_t size1 = ft::size<func_with_int_t>();
  constexpr size_t size2 = ft::size<func_with_four_ints_t>();
  constexpr size_t size3 = ft::size<func_with_many_ints_t>();
  constexpr size_t size12 =
      ft::size<func_with_int_t, func_with_four_ints_t>();
  constexpr size_t size123 =
      ft::size<func_with_int_t, func_with_four_ints_t, func_with_many_ints_t>();

  std::cout << "size0a:" << size0a << std::endl;
  std::cout << "size0b:" << size0b << std::endl;
  std::cout << "size1:" << size1 << std::endl;
  std::cout << "size2:" << size2 << std::endl;
  std::cout << "size3:" << size3 << std::endl;
  std::cout << "size12:" << size12 << std::endl;
  std::cout << "size123:" << size123 << std::endl;
}

int main(int argc, char const *argv[]) {
  calc_size();
  use_fixfunc();
  use_stdfunction();
}
