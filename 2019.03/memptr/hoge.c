#include <stddef.h>
#include <stdio.h>
#include <time.h>

void show_sec(){
  time_t timer =time(NULL);
  struct tm *local = localtime(&timer);
  printf( "%d\n", local->tm_sec );
}

void show_min(){
  time_t timer =time(NULL);
  struct tm *local = localtime(&timer);
  printf( "%d\n", local->tm_min );
}

void show_xxx( size_t offset ){
  time_t timer =time(NULL);
  struct tm *local = localtime(&timer);
  printf( "%d\n", *(int*)(((char*)local)+offset) );
}

void use_show_xxx(void){
  show_xxx(offsetof(struct tm, tm_sec));
}

int main(int argc, char const * argv[]) {
  use_show_xxx();
  if ( 1<argc && argv[1][0]=='1' ){
    show_sec();
    show_xxx(offsetof(struct tm, tm_sec));
  } else {
    show_min();
    show_xxx(offsetof(struct tm, tm_min));
  }
  return 0;
}
