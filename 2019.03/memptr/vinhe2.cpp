#include <array>
#include <iostream>

struct base0 {
  virtual void bar() { std::cout << "base0::bar\n"; }
};

struct base1 {
  virtual void baz() { std::cout << "base1::baz\n"; }
};

struct derived : public base0, public base1 {
  using base0::bar;
  using base1::baz;
};

template <typename klass>
void show_one(char const *name, void (klass::*member)()) {
  auto ary = *reinterpret_cast<std::array<size_t, 2> *>(&member);
  std::cout << name << "=" << 
  std::dec << sizeof(member) << ": " << std::hex << ary[0] << ":" << ary[1] << std::endl;
}

void show() {
  show_one("&derived::bar", &derived::bar); // => 「&derived::foo: 1:0」を出力
  show_one("&derived::baz", &derived::baz); // => 「&derived::foo: 1:0」を出力
  void (derived::*hoge)() = &derived::bar;
  void (derived::*fuga)() = &derived::baz;
  (derived().*hoge)();
  (derived().*fuga)();
  show_one("&derived::bar", hoge); // => 「&derived::foo: 1:0」を出力
  show_one("&derived::baz", fuga); // => 「&derived::foo: 1:0」を出力
}

int main(int argc, char const *argv[]) {
  show();
}
