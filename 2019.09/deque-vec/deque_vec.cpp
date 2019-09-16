#include <chrono>
#include <cstdint>
#include <array>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace std::chrono;

template <typename element_t>
inline void push_front(deque<element_t> &c, element_t v) {
  c.push_front(v);
}

template <typename element_t>
inline void push_front(vector<element_t> &c, element_t v) {
  c.insert(c.begin(), v);
}

template <typename element_t>
inline void resize(deque<element_t> &c, size_t v) {
}

template <typename element_t>
inline void resize(vector<element_t> &c, size_t v) {
  c.resize(v);
}

struct vec_reserver{
  template< typename container_t>
  static void reserve(container_t & c, size_t size ){
    c.reserve(size);
  }
};

struct null_reserver{
  template< typename container_t>
  static void reserve(container_t & , size_t ){
  }
};

template <typename container_t, typename reserver_t> //
struct tester {
  static constexpr size_t trial_count = 256;
  using value_type = typename container_t::value_type;
  int64_t impl(size_t size) {
    array<container_t, trial_count> cc;
    for( auto & c : cc ){
      reserver_t::reserve(c,size+1);
      resize(c, size);
      value_type v{};
      for (auto &e : c) {
        e = ++v;
      }
    }
    auto start = high_resolution_clock::now();
    for( auto & c : cc ){
      push_front(c, value_type{});
    }
    auto end = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end - start).count();
  }

  void run(size_t size, char const *name) {
    vector<int64_t> ticks(20);
    for (auto &e : ticks) {
      e = impl(size);
    }
    auto min = *min_element(ticks.cbegin(), ticks.cend());
    cout << name << "," << size << "," << min*1e-3 << endl;
  }
};

int main() {
  for (size_t size = 1; size <= (1 << 16); size*=2) {
    tester<vector<char>, vec_reserver>().run(size, "vector<char>+reserve");
    tester<vector<char>, null_reserver>().run(size, "vector<char>");
    tester<deque<char>, null_reserver>().run(size, "deque<char>");
    tester<vector<int32_t>, vec_reserver>().run(size, "vector<int32_t>+reserve");
    tester<vector<int32_t>, null_reserver>().run(size, "vector<int32_t>");
    tester<deque<int32_t>, null_reserver>().run(size, "deque<int32_t>");
  }
}
