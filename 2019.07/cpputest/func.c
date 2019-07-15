#include <stdio.h>

static int static_func(int param) {
    printf("static_func %d\n", param);
    return param;
}

int public_func(int param) {
    printf("public func %d\n", param);
    return static_func(param);
}