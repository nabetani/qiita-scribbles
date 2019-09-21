#include <functional>
#include <iostream>

#include "fixfunc.hpp"
#include "gtest/gtest.h"

namespace {

struct with_counter {
  static int counter;
  with_counter() { ++counter; }

  with_counter(with_counter const &that) : proc_(that.proc_) { ++counter; }
  ~with_counter() { --counter; }
  std::function<int(int)> proc_;
  int operator()(int a) { return proc_(a); }
};

struct without_counter {
  std::function<int(int)> proc_;
  int operator()(int a) { return proc_(a); }
};

int with_counter ::counter = 0;

TEST(with_counter, test_tester) {
  with_counter::counter = 0;
  {
    with_counter w;
    ASSERT_EQ(1, with_counter::counter);
  }
  ASSERT_EQ(0, with_counter::counter);
}

TEST(with_counter, count_ctor_dtor) {
  with_counter::counter = 0;
  {
    nabetani::fixfunc<int(int), 100> f{with_counter{}};
    ASSERT_EQ(1, with_counter::counter);
    {
      auto g = f;
      ASSERT_EQ(2, with_counter::counter);
      g = f;
      ASSERT_EQ(2, with_counter::counter);
      g = g;
      ASSERT_EQ(2, with_counter::counter);
      g = with_counter{};
      ASSERT_EQ(2, with_counter::counter);
      g = without_counter{};
      ASSERT_EQ(1, with_counter::counter);
    }
    ASSERT_EQ(1, with_counter::counter);
  }
  ASSERT_EQ(0, with_counter::counter);
}

TEST(call, object_with_funcop) {
  int call_count = 0;
  int arg = 0;
  with_counter::counter = 0;
  with_counter w;
  ASSERT_EQ(1, with_counter::counter);
  w.proc_ = [&](int a) -> int {
    arg = a;
    ++call_count;
    return 123 + a;
  };
  nabetani::fixfunc<int(int), 100> f = w;
  ASSERT_EQ(2, with_counter::counter);
  auto r = f(456);
  ASSERT_EQ(123 + 456, r);
  ASSERT_EQ(456, arg);
  ASSERT_EQ(1, call_count);

  auto g = f;
  ASSERT_EQ(3, with_counter::counter);
  auto r2 = f(789);
  ASSERT_EQ(123 + 789, r2);
  ASSERT_EQ(789, arg);
  ASSERT_EQ(2, call_count);
}

TEST(call, lambda) {
  int cc0 = 0;
  nabetani::fixfunc<int(int), 100> f = [&](int a) -> int {
    ++cc0;
    return a + 1000;
  };
  auto r0 = f(1);
  ASSERT_EQ(1001, r0);
  ASSERT_EQ(1, cc0);
  int cc1 = 0;
  f = [&](int a) -> int {
    ++cc1;
    return a + 2000;
  };
  auto r1 = f(2);
  ASSERT_EQ(2002, r1);
  ASSERT_EQ(1, cc0);
  ASSERT_EQ(1, cc1);
}

int global_cc = 0;

int func0(int a) {
  ++global_cc;
  return 3000 + a;
}

int func1(int a) {
  ++global_cc;
  return 4000 + a;
}

TEST(call, funcptr) {
  global_cc = 0;
  nabetani::fixfunc<int(int), 100> f = &func0;
  auto r0 = f(11);
  ASSERT_EQ( 3011, r0 );
  ASSERT_EQ( 1, global_cc );
  f = &func1;
  auto r1 = f(22);
  ASSERT_EQ( 4022, r1 );
  ASSERT_EQ( 2, global_cc );
}

TEST(call, func) {
  global_cc = 0;
  nabetani::fixfunc<int(int), 100> f = func0;
  auto r0 = f(11);
  ASSERT_EQ( 3011, r0 );
  ASSERT_EQ( 1, global_cc );
  f = func1;
  auto r1 = f(22);
  ASSERT_EQ( 4022, r1 );
  ASSERT_EQ( 2, global_cc );
}

} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
