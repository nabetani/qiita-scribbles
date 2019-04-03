#include <cstddef>
#include <ctime>
#include <iostream>

void show_sec(){
  auto timer = std::time(NULL);
  auto local = localtime(&timer);
  std::cout << local->tm_sec << std::endl;
}

void show_min(){
  auto timer = std::time(NULL);
  auto local = localtime(&timer);
  std::cout << local->tm_min << std::endl;
}

void show_xxx( int tm::*member ){
  auto timer = std::time(NULL);
  auto local = localtime(&timer);
  std::cout << local->*member << std::endl;
}

void use_show_xxx(void){
  show_xxx(&tm::tm_sec);
}

int main(int argc, char const * argv[]) {
  use_show_xxx();
  if ( 1<argc && argv[1][0]=='1' ){
    show_sec();
    show_xxx(&tm::tm_sec);
  } else {
    show_min();
    show_xxx(&tm::tm_min);
  }
  return 0;
}
