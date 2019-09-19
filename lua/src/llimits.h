#ifndef __LLIMITS__
#define __LLIMITS__

#include "lua.h"

// 用来表示较小的自然数
typedef unsigned char lu_byte;

// 官方定义这玩意为了高亮提示。。。
#define cast(t, exp) ((t)(exp))

// at least 4 byte
#if LUAI_BITSINT >= 32
typedef unsigned int Instruction;
#else
typedef unsigned long Instruction;
#endif

#endif /* __LLIMITS__ */