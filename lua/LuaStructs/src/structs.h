#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "common.h"

#define lmod(s, size) \
	(check_exp((size & (size - 1)) == 0, (cast(int, (s) & ((size) - 1)))))
#define getstr(ts) \
	check_exp(sizeof((ts)->extra), cast(char *, (ts)) + sizeof(UTString))
#define sizelstring(l) (sizeof(union UTString) + ((l) + 1) * sizeof(char))

typedef struct GCObject GCObject;

typedef union Value {
    GCObject *gc;
	void *p; // light userdata
	int b; // booleans
	integer i;
	number n;
} Value;

#define TValuefields Value value_; int tt_

typedef struct TValue {
	TValuefields;
} TValue;

typedef TValue *StkId;

#define NILCONSTANT {NULL}, LUA_TNIL

#define nilobject (&nilobject_)
// 如果不加extern则视为定义，会多重定义
extern const TValue nilobject_;

#define CommonHeader GCObject *next; byte tt; byte marked

struct GCObject {
	CommonHeader;
};

typedef struct TString {
	CommonHeader;
	byte extra;
	byte shrlen;
	unsigned int hash;
	union {
		size_t lnglen;
		struct TString *hnext;
	} u;
} TString;

// 通过高4位判断是长字符串还是短字符串
// 0b00000100
#define TSHRSTR (LUA_TSTRING | (0 << 4))
// 0b00010100
#define TLNGSTR (LUA_TSTRING | (1 << 4))
#define LUA_TNUMFLT    (LUA_TNUMBER | (0 << 4))
#define LUA_TNUMINT    (LUA_TNUMBER | (1 << 4))

// union性质：会按最大数据类型取大小
typedef union {
	number n;
	double u;
	void *s;
	integer i;
	long l;
} L_Umaxalign;

typedef union UTString {
	L_Umaxalign dummy; // 确保字符串的最大对齐方式
	TString tsv;
} UTString;

// 相同的短字符串，同一个Lua State只存唯一一份，被存放在global_State的strt域中，这称为字符串内部化。

typedef struct stringtable {
	TString **hash;
	int nuse;
	int size;
} stringtable;

typedef void * (*lua_Allooc) (void *ud, void *ptr, size_t osize, size_t nsize);

typedef struct global_State {
	lua_Allooc frealloc;
	stringtable strt;
	unsigned int seed;
	l_mem GCdebt;
	TString *strcache[53][2];
	GCObject *allgc;
	byte currentwhite;
} global_State;

struct lua_State {
	CommonHeader;
	global_State *l_G;
};

typedef struct LX {
	byte extra_[sizeof(void *)];
	lua_State l;
} LX;

typedef struct LG {
	LX l;
	global_State g;
} LG;

// Lua 表相关
typedef union TKey {
    struct {
        TValuefields;
        int next;
    } nk;
    TValue tvk;
} TKey;

typedef struct Node {
    TValue i_val;
    TKey i_key;
} Node;

typedef struct Table {
    CommonHeader;
    byte flags;
    byte lsizenode;
    unsigned int sizearray;
    TValue *array;
    Node *node;
    Node *lastfree;
    struct Table *metatable;
    GCObject *gclist;
} Table;

// 2 ^ n
#define twoto(x) (1<<(x))
#define sizenode(t) (twoto((t)->lsizenode))
#define gnode(t, i) (&(t)->node[i])

#define ivalue(o) (val_(o).i)
#define fltvalue(o) (val_(o).n)
#define bvalue(o) (val_(o).b)
#define tsvalue(o) gco2ts(val_(o).gc)

union GCUnion {
	GCObject gc;
	struct TString ts;
	struct lua_State th;
};

lua_State * l_newstate (void);
void l_resize (lua_State *L, int newsize);
TString *l_createlngstrobj (lua_State *L, size_t l);
extern GCObject *luaC_newobj(lua_State *L, int tt, size_t sz);
unsigned int l_hashlongstr(TString *ts);
extern int luaV_equalobj (lua_State *L, const TValue *t1, const TValue *t2);

#define G(L) ((L)->l_G)























#endif /* __STRUCTS_H__ */
