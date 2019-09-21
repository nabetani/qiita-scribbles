#include "fixfunc.hpp"
#include "gtest/gtest.h"

namespace {

struct with_counter {
  static int counter;
  with_counter() { ++counter; }

  with_counter(with_counter const &that) { ++counter; }
  ~with_counter() { --counter; }
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
    nabetani::fixfunc<int(int), 100> f{ with_counter{} };
    ASSERT_EQ(1, with_counter::counter);
    {
      auto g = f;
      ASSERT_EQ(2, with_counter::counter);
    }
    ASSERT_EQ(1, with_counter::counter);
  }
  ASSERT_EQ(0, with_counter::counter);
}

} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
