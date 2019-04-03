#include <array>
#include <iostream>

struct base0 {
  virtual void bar() { std::cout << "base0::bar\n"; }
};

struct base1 {
  virtual void baz() { std::cout << "base1::baz\n"; }
};

struct base2 {
  virtual void qux() { std::cout << "base2::qux\n"; }
};

struct derived : public base0, public base1, public base2 {
  virtual void foo() { std::cout << "derived::baz\n"; }
};

void show_one(char const *name, void (derived::*member)()) {
  auto ary = *reinterpret_cast<std::array<size_t, 2> *>(&member);
  std::cout << name << ": " << std::hex << ary[0] << ":" << ary[1] << std::endl;
}

void show() {
  show_one("&derived::foo",
           &derived::foo); // => 「&derived::foo: 9:0」を出力
  show_one("&derived::bar",
           &derived::bar); // => 「&derived::bar: 1:0」を出力
  show_one("&derived::baz",
           &derived::baz); // => 「&derived::baz: 1:8」を出力
  show_one("&derived::qux",
           &derived::qux); // => 「&derived::qux: 1:10」を出力
}

int main(int argc, char const *argv[]) { show(); }
