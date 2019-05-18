
struct foo {
  int x, y;
  void hoge();
  void fuga();
};

void foo::hoge(){}
void foo::fuga(){}

int main() {

  int foo::*xory = &foo::x;
  void (foo::*memfunc)() = &foo::hoge;

  foo obj;
  foo *ptr = &obj;
  obj.*xory = 1;
  (obj.*memfunc)();
  ptr->*xory = 2;
  (ptr->*memfunc)();
}