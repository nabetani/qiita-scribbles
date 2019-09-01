#include <chrono>
#include <cstdint>
#include <deque>
#include <iostream>
#include <vector>
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

template <typename container_t> //
struct tester {
  int64_t impl(size_t size) {
    container_t c(size);
    typename container_t::value_type v{};
    for (auto &e : c) {
      e = ++v;
    }
    auto start = high_resolution_clock::now();
    push_front(c, v);
    auto end = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end - start).count();
  }

  void run(size_t size, char const *name) {
    // Preparation gymnastics
    impl(size);
    // Preparation gymnastics
    impl(size);
    //  Action!
    vector<int64_t> ticks(20);
    for (auto &e : ticks) {
      e = impl(size);
    }
    auto min = *min_element(ticks.cbegin(), ticks.cend());
    cout << name << "," << size << "," << min << endl;
  }
};

int main() {
  for (size_t size = 1; size < (1 << 16); size*=2) {
    tester<vector<char>>().run(size, "vector<char>");
    tester<deque<char>>().run(size, "deque<char>");
  }
}
