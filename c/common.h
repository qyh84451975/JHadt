#include <stdio.h>

#define UNUSED(x) ((void)(x))
// 这个宏如果用分号分割，会存在潜在风险。
#define writeerr(msg) (fprintf(stderr, "%s\n", msg), exit(1))

