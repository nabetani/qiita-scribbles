// clang++ -std=c++11 -Wall hoge.cp
#include <iostream>

int foo(char const *title) {
  std::cout << title << "\n";
  return 0;
}

struct dtype {
  dtype() { std::cout << "dtype default-ctor\n"; }
  dtype(char const *label) { std::cout << "dtype " << label << "\n"; }
};

struct btype {
  btype() { std::cout << "btype default-ctor\n"; }
};

struct hoge {
  int a = foo("a");
  btype b;
  int c = foo("c");
  dtype d;
  int e = foo("e-decl");
  hoge()                  //
      : e(foo("e-ctor")), // warning: field 'e' will be initialized after field 'd'
        d("hoge ctor")    //
  {
    std::cout << "in hoge::hoge\n";
  }
};

int main() {
  hoge h;
  return 0;
}
