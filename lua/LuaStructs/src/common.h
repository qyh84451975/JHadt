#ifndef __COMMON_H__
#define __COMMON_H__

#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct lua_State lua_State;

#define MAX_INT INT_MAX
#define MAXABITS    cast_int(sizeof(int) * CHAR_BIT - 1)
#define MAXASIZE    (1u << MAXABITS)

#define LUA_TNONE				(-1)
#define LUA_TNIL				0
#define LUA_TBOOLEAN			1
#define LUA_TLIGHTUSERDATA		2
#define LUA_TNUMBER				3
#define LUA_TSTRING				4
#define LUA_TTABLE				5
#define LUA_TFUNCTION			6
#define LUA_TUSERDATA			7
#define LUA_TTHREAD				8
#define LUA_NUMTAGS				9

#define BIT_ISCOLLECTABLE    (1 << 6)
#define ctb(t)            ((t) | BIT_ISCOLLECTABLE)

// 基本类型(0-3bits)
#define novariant(x) ((x) & 0x0F)
#define rttype(o)    ((o)->tt_)
#define ttype(o)    (rttype(o) & 0x3F)
#define val_(o)     ((o)->value_)
#define ttnov(o)    (novariant(rttype(o)))
#define checktag(o,t)        (rttype(o) == (t))
#define checktype(o,t)        (ttnov(o) == (t))
#define ttisnumber(o)        checktype((o), LUA_TNUMBER)
#define ttisfloat(o)        checktag((o), LUA_TNUMFLT)
#define ttisinteger(o)        checktag((o), LUA_TNUMINT)
#define ttisnil(o)        checktag((o), LUA_TNIL)
#define ttisboolean(o)        checktag((o), LUA_TBOOLEAN)
#define ttisstring(o)        checktype((o), LUA_TSTRING)
#define ttisshrstring(o)    checktag((o), ctb(TSHRSTR))
#define ttislngstring(o)    checktag((o), ctb(TLNGSTR))
#define ttistable(o)        checktag((o), ctb(LUA_TTABLE))
#define ttisfunction(o)        checktype(o, LUA_TFUNCTION)

#define l_assert assert
#define check_exp(c, e) (e)

typedef long long integer;
typedef double number;
typedef unsigned char byte;
typedef ptrdiff_t l_mem;

#define MAX_SIZET	((size_t)(~(size_t)0))
#define MAX_SIZE	(sizeof(size_t) < sizeof(integer) ? MAX_SIZET \
                          : (size_t)(LLONG_MAX))
#define lua_numbertointeger(n, p) \
    ((n) >= (number)(LLONG_MIN) && \
     (n) < -(number)(LLONG_MIN) && \
    (*(p) = (integer)(n), 1))

#define cast(t, exp) ((t)(exp))
#define cast_int(i) cast(int, (i))
#define cast_byte(i) cast(byte, (i))
#define cast_u(o) cast(union GCUnion *, (o))

#define luaM_reallocv(L, b, on, n, e) \
	luaM_realloc_(L, (b), (on) * (e), (n) * (e))

#define luaM_reallocvector(L, v, oldn, n, t) \
	((v) = cast(t *, luaM_reallocv(L, v, oldn, n, sizeof(t))))

#define luaM_newobject(L, tag, s) \
	luaM_realloc_(L, NULL, tag, (s))

#define WHITE0BIT	0  /* object is white (type 0) */
#define WHITE1BIT	1  /* object is white (type 1) */
#define BLACKBIT	2  /* object is black */
#define FINALIZEDBIT	3  /* object has been marked for finalization */
#define bitmask(b)		(1<<(b))
#define bit2mask(b1,b2)		(bitmask(b1) | bitmask(b2))
#define WHITEBITS	bit2mask(WHITE0BIT, WHITE1BIT)
#define luaC_white(g) cast(byte, (g)->currentwhite & WHITEBITS)
#define gco2ts(o) \
	check_exp(novariant((o)->tt) == LUA_TSTRING, &((cast_u(o))->ts))

extern void * luaM_realloc_ (lua_State *L, void *block, size_t osize, size_t size);

unsigned int makeseed (void);
unsigned int l_hash (const char *str, size_t len, unsigned int seed);

#endif /* __COMMON_H__ */
