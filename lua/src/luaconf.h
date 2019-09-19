#ifndef __LUA_CONF__
#define __LUA_CONF__

#include <limits.h>
#include <stddef.h>

// mark for extern (const)
#define LUAI_FUNC extern
#define LUAI_DDEC LUAI_FUNC

#if ((INT_MAX >> 15) >> 15) >= 1
#define LUAI_BITSINT 32
#else
#define LUAI_BITSINT 16
#endif

#define LUA_NUMBER double
#define LUA_INTEGER long long


#endif /* __LUA_CONF__ */