#include <array>
#include <iostream>

struct root {
  virtual void foo() { std::cout << "root::foo\n"; }
};

struct base0: public virtual root {
  virtual void bar() { std::cout << "base0::bar\n"; }
  virtual void qux(){}
};

struct base1: public virtual root {
  virtual void baz() { std::cout << "base1::baz\n"; }
  virtual void qux(){}
};

struct derived : public base0, public base1 {
};

template <typename klass>
void show_one(char const *name, void (klass::*member)()) {
  auto ary = *reinterpret_cast<std::array<size_t, 2> *>(&member);
  std::cout << name << "=" << 
  std::dec << sizeof(member) << ": " << std::hex << ary[0] << ":" << ary[1] << std::endl;
}

void show() {
  show_one("&derived::foo", &derived::foo); // => 「&derived::foo: 1:0」を出力
  show_one("&derived::bar", &derived::bar); // => 「&derived::foo: 1:0」を出力
  show_one("&derived::baz", &derived::baz); // => 「&derived::foo: 1:0」を出力
  show_one("&derived::base0::qux", &derived::base0::qux); // => 「&derived::foo: 1:0」を出力
  show_one("&derived::base1::qux", &derived::base1::qux); // => 「&derived::foo: 1:0」を出力
  show_one("&base0::foo", &base0::foo); // => 「&derived::foo: 1:0」を出力
  show_one("&base0::bar", &base0::bar); // => 「&derived::foo: 1:0」を出力
}

int main(int argc, char const *argv[]) {
  show();
}
