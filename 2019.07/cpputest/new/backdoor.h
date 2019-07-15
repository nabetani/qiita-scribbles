#pragma once
#if defined __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C extern
#endif

EXTERN_C
int static_func_backdoor(int param);
