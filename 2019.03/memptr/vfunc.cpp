#include <array>
#include <iostream>

struct base {
  virtual void foo() { std::cout << "base::foo\n"; }
  void bar() { std::cout << "base::bar\n"; }
  virtual void baz() { std::cout << "base::baz\n"; }
};

struct derived : public base {
  void foo() override { std::cout << "derived::foo\n"; }
  void bar() { std::cout << "derived::bar\n"; }
};

void sample() {
  auto m_b_foo = &base::foo;
  auto m_b_bar = &base::bar;
  auto m_d_foo = &derived::foo;
  auto m_d_bar = &derived::bar;

  base b;
  derived d;
  base *b_d = &d;

  (b.*m_b_foo)(); // 「base::foo」を出力
  (b.*m_b_bar)(); // 「base::bar」を出力
  //(b.*m_d_foo)();// コンパイルエラー
  //(b.*m_d_bar)();// コンパイルエラー

  (b_d->*m_b_foo)(); // 「derived::foo」を出力
  (b_d->*m_b_bar)(); // 「base::bar」を出力
  //(b_d->*m_d_foo)();// コンパイルエラー
  //(b_d->*m_d_bar)();// コンパイルエラー

  (d.*m_b_foo)(); // 「derived::foo」を出力
  (d.*m_b_bar)(); // 「base::bar」を出力

  (d.*m_d_foo)(); // 「derived::foo」を出力
  (d.*m_d_bar)(); // 「derived::bar」を出力
}

template <typename klass>
void show_one(char const *name, void (klass::*member)()) {
  auto ary = *reinterpret_cast<std::array<size_t, 2> *>(&member);
  std::cout << name << ": " << std::hex << ary[0] << ":" << ary[1] << std::endl;
}

void show() {
  show_one("&base::foo", &base::foo); // => 「&base::foo: 1:0」を出力
  show_one("&base::bar", &base::bar); // => 「&base::bar: 103cc5c00:0」を出力
  show_one("&base::baz", &base::bar); // => 「&base::bar: 103cc5c00:0」を出力
  show_one("&derived::foo", &derived::foo); // => 「&derived::foo: 1:0」を出力
  show_one("&derived::bar",
           &derived::bar); // => 「&derived::bar: 103cc5c30:0」を出力
  show_one("&derived::baz",
           &derived::baz); // => 「&derived::bar: 103cc5c30:0」を出力
  show_one<derived>("&derived::foo", &derived::foo); // => 「&derived::foo: 1:0」を出力
  show_one<derived>("&derived::bar",
           &derived::bar); // => 「&derived::bar: 103cc5c30:0」を出力
  show_one<derived>("&derived::baz",
           &derived::baz); // => 「&derived::bar: 103cc5c30:0」を出力
}

int main(int argc, char const *argv[]) {
  sample();
  show();
}
