// -std=c++17 -Wall -O3
#include <chrono>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <vector>

template <typename E> //
inline void push_front(std::vector<E> &c, E const &e) {
  c.insert(c.begin(), e);
}

template <typename E> //
inline void push_front(std::deque<E> &c, E const &e) {
  c.push_front(e);
}

template <typename E> //
inline void push_front(std::list<E> &c, E const &e) {
  c.push_front(e);
}

template <size_t size_> struct element {
  char m[size_];
  element() : m{} {}
};

using e4 = element<4>;
using e16 = element<16>;
using e64 = element<64>;
using e256 = element<256>;
using e1024 = element<1024>;
using e4096 = element<4096>;
using e16384 = element<16384>;
using e65536 = element<65536>;
using e262144 = element<262144>;
using e1048576 = element<1048576>;

template <typename C> //
int test_impl(std::function<C()> const &proc) {
  using namespace std::chrono;
  using clock = high_resolution_clock;

  C cont[5000];
  for (auto &c : cont) {
    c = proc();
  }
  typename C::value_type e;

  auto start = clock::now();
  for (auto &c : cont) {
    for (int i = 0; i < 1; ++i) {
      push_front(c, e);
    }
  }
  auto end = clock::now();
  std::cout << duration_cast<nanoseconds>(end - start).count() << std::endl;
  return 0;
}

template <typename E> //
int test(int s, char t) {
  switch (t) {
  case 'V':
    return test_impl<std::vector<E>>([s]() {
      auto r = std::vector<E>(s);
      r.reserve(s + 1);
      return r;
    });
  case 'v':
    return test_impl<std::vector<E>>([s]() { return std::vector<E>(s); });
  case 'd':
    return test_impl<std::deque<E>>([s]() { return std::deque<E>(s); });
  case 'l':
    return test_impl<std::list<E>>([s]() { return std::list<E>(s); });
  default:
    return 1;
  }
}

int main(int argc, char const *argv[]) {
  if (argc != 4) {
    return 1;
  }
  int e = std::atoi(argv[1]);
  int s = std::atoi(argv[2]);
  switch (e) {
  case 4:
    return test<e4>(s, *argv[3]);
  case 16:
    return test<e16>(s, *argv[3]);
  case 64:
    return test<e64>(s, *argv[3]);
  case 256:
    return test<e256>(s, *argv[3]);
  case 1024:
    return test<e1024>(s, *argv[3]);
  case 4096:
    return test<e4096>(s, *argv[3]);
  case 16384:
    return test<e16384>(s, *argv[3]);
  case 65536:
    return test<e65536>(s, *argv[3]);
  case 262144:
    return test<e262144>(s, *argv[3]);
  case 1048576:
    return test<e1048576>(s, *argv[3]);
  default:
    return 1;
  }
}
