#include "common.h"
#include "structs.h"

void * luaM_realloc_ (lua_State *L, void *block, size_t osize, size_t nsize)
{
	void *newblock;
	global_State *g = G(L);
	size_t realosize = (block) ? osize : 0;
	l_assert((realosize == 0) == (block == NULL));
	newblock = (*g->frealloc)(NULL, block, osize, nsize);
	if (newblock == NULL && nsize > 0) {
		l_assert(nsize > realosize);
		newblock = (*g->frealloc)(NULL, block, osize, nsize);
	}
	l_assert((nsize == 0) == (newblock == NULL));
	g->GCdebt = (g->GCdebt + nsize) - realosize;
	return newblock;
}

GCObject *luaC_newobj(lua_State *L, int tt, size_t sz)
{
	global_State *g = G(L);
	// novariant(tt)判断基础类型(0-3bits)
	GCObject *o = cast(GCObject *, luaM_newobject(L, novariant(tt), sz));
	o->marked = luaC_white(g);
	o->tt = tt; // 类型
	o->next = g->allgc;
	g->allgc = o; // 将新创建的obj添加到allgc链表最后
	return o;
}

int luaV_equalobj (lua_State *L, const TValue *t1, const TValue *t2)
{
    if (ttype(t1) != ttype(t2)) {
        if (ttnov(t1) != ttnov(t2) || ttnov(t1) != LUA_TNUMBER)
            return 0;
        else {
            integer i1, i2;
            
        }
    }
}
