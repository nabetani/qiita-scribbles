#include "backdoor.h"
#include "func.c"

int static_func_backdoor(int param)
{
  return static_func(param);
}

