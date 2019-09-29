#include "structs.h"

const TValue nilobject_ = {NILCONSTANT};

static void * l_alloc (void *ud, void *ptr, size_t osize, size_t nsize)
{
	(void)ud; (void)osize;
	if (nsize == 0) {
		free(ptr);
		return NULL;
	}
	else {
		return realloc(ptr, nsize);
	}
}

//static int panic (const char *msg)
//{
//    ((void)(fprintf(stderr, ("PANIC: unprotected error in call (%s)\n"), (msg))), fflush(stderr));
//    return 0;
//}

lua_State * l_newstate ()
{
	lua_State *L;
	global_State *g;
	LG *l = cast(LG *, l_alloc(NULL, NULL, LUA_TTHREAD, sizeof(LG)));
	if (l == NULL) return NULL;
	L = &l->l.l;
	g = &l->g;
	L->tt = LUA_TTHREAD;
	L->l_G = g;
	g->frealloc = &l_alloc;
	g->seed = makeseed();
	g->strt.nuse = g->strt.size = 0;
	g->strt.hash = NULL;
	g->GCdebt = 0;
	g->currentwhite = bitmask(WHITE0BIT);
	return L;
}
