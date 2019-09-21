#include "fixfunc.hpp"
#include <functional>
#include <iostream>
#include <string>
#include <chrono>

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
  constexpr size_t size12 = ft::size<func_with_int_t, func_with_four_ints_t>();
  constexpr size_t size123 =
      ft::size<func_with_int_t, func_with_four_ints_t, func_with_many_ints_t>();

  std::cout << "size0a:" << size0a << std::endl;
  std::cout << "size0b:" << size0b << std::endl;
  std::cout << "size1:" << size1 << std::endl;
  std::cout << "size2:" << size2 << std::endl;
  std::cout << "size3:" << size3 << std::endl;
  std::cout << "size12:" << size12 << std::endl;
  std::cout << "size123:" << size123 << std::endl;

  using f0a = nabetani::fixfunc<int(int, int), size0a>;
  using f1 = nabetani::fixfunc<int(int, int), size1>;
  using f2 = nabetani::fixfunc<int(int, int), size2>;
  using f3 = nabetani::fixfunc<int(int, int), size3>;

  f0a v0a = simple_func;
  f1 v1 = func_with_int_t{};
  f2 v2 = func_with_four_ints_t{};
  f3 v3 = func_with_many_ints_t{};

#if 0
  using f0am = nabetani::fixfunc<int(int,int), size0a-1>;
  using f1m = nabetani::fixfunc<int(int,int), size1-1>;
  using f2m = nabetani::fixfunc<int(int,int), size2-1>;
  using f3m = nabetani::fixfunc<int(int,int), size3-1>;

  f0am v0am = simple_func; // compile error
  f1m v1m = func_with_int_t{}; // compile error
  f2m v2m = func_with_four_ints_t{}; // compile error
  f3m v3m = func_with_many_ints_t{}; // compile error
#endif
}

namespace bench {
int f0(int a, int b) { return a + b; }

struct f1_t {
  int m;
  int operator()(int a, int b) const { return a + b + m; }
};

struct f2_t {
  int m, n, o, p;
  int operator()(int a, int b) const { return a + b + m + n + o + p; }
};

} // namespace bench

template <typename func_t> std::uint64_t benchmark_subst() {
  using namespace bench;
  using clock = std::chrono::steady_clock;
  auto t0 = clock::now();
  func_t f = simple_func;
  for (int i = 0; i < 100000; ++i) {
    f = f0;
    f = f1_t{1};
    f = f2_t{1,2,3,4};
  }
  auto t1 = clock::now();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();
}

template <typename func_t> std::uint64_t benchmark_call() {
  using namespace bench;
  using clock = std::chrono::steady_clock;
  auto t0 = clock::now();
  func_t o0 = f0;
  func_t o1 = f1_t{1};
  func_t o2 = f2_t{1,2,3,4};
  func_t o3 = [](int a, int b)->int{
    return a+b*2;
  };
  int r = 0;
  for (int i = 0; i < 100000; ++i) {
    r = o3(r,o0(o1(11,r), o2(22,r)));
  }
  auto t1 = clock::now();
  if (r == 0x1234) {
    std::cout << "unexpected\n";
  }
  return std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();
}

void benchmark() {
  using namespace bench;
  using ft = nabetani::func_type<int(int, int)>;
  constexpr size_t size = ft::size<decltype(f0), f1_t, f2_t>();
  {
    std::cout << "subst:" << std::endl;
    std::uint64_t fixed = 1ULL << 60;
    std::uint64_t standard = 1ULL << 60;
    for (int i = 0; i < 50; ++i) {
      fixed = std::min<std::uint64_t>(
          fixed, benchmark_subst<nabetani::fixfunc<int(int, int), size>>());
      standard = std::min<std::uint64_t>(
          standard, benchmark_subst<std::function<int(int, int)>>());
    }
    std::cout << "    fixed: " << fixed * 1e-3
              << ", standard: " << standard * 1e-3 << std::endl;
  }
  {
    std::cout << "call:" << std::endl;
    std::uint64_t fixed = 1ULL << 60;
    std::uint64_t standard = 1ULL << 60;
    for (int i = 0; i < 50; ++i) {
      fixed = std::min<std::uint64_t>(
          fixed, benchmark_call<nabetani::fixfunc<int(int, int), size>>());
      standard = std::min<std::uint64_t>(
          standard, benchmark_call<std::function<int(int, int)>>());
    }
    std::cout << "    fixed: " << fixed * 1e-3
              << ", standard: " << standard * 1e-3 << std::endl;
  }
}

int main(int argc, char const *argv[]) {
  calc_size();
  use_fixfunc();
  use_stdfunction();
  benchmark();
}
