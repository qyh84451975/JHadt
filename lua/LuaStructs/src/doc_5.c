/**
 * lua字符串
 */


#include "structs.h"
#include <stddef.h>
#include <string.h>

/**
 * int memcmp (const void *str1, const void *str2, size_t n)
 * 将str1和str2的前n个字节做比较
 * 返回值<0 str1 < str2
 * 返回值>0 str1 > str2
 * 返回值=0 str1 == str2
 */

void l_sinit(lua_State *L)
{
//    global_State *g = G(L);
//    int i, j;
	l_resize(L, 128);
}

void l_remove (lua_State *L, TString *ts)
{
	stringtable *tb = &G(L)->strt;
	TString **p = &tb->hash[lmod(ts->hash, tb->size)];
	while (*p != ts)
		p = &(*p)->u.hnext;
	*p = (*p)->u.hnext;
	tb->nuse--;
}

unsigned int l_hashlongstr(TString *ts)
{
    l_assert(ts->tt == TLNGSTR);
    if (ts->extra == 0) {
        ts->hash = l_hash(getstr(ts), ts->u.lnglen, ts->hash);
        ts->extra = 1;
    }
    return ts->hash;
}

void l_resize (lua_State *L, int newsize)
{
	int i;
	stringtable *tb = &G(L)->strt;
	if (newsize > tb->size) {
		luaM_reallocvector(L, tb->hash, tb->size, newsize, TString *);
		for (i = tb->size; i < newsize; i++)
			tb->hash[i] = NULL;
	}
	for (i = 0; i < tb->size; i++) {
		TString *p = tb->hash[i];
		tb->hash[i] = NULL;
		while (p) {
			TString *hnext = p->u.hnext;
			unsigned int h = lmod(p->hash, newsize);
			p->u.hnext = tb->hash[h];
			tb->hash[h] = p;
			p = hnext;
		}
	}
	if (newsize < tb->size) {
		l_assert(tb->hash[newsize] == NULL && tb->hash[tb->size - 1] == NULL);
		luaM_reallocvector(L, tb->hash, tb->size, newsize, TString *);
	}
	tb->size = newsize;
}

static TString *createstrobj (lua_State *L, size_t l, int tag, unsigned int h)
{
	TString *ts;
	GCObject *o;
	size_t totalsize;
	totalsize = sizelstring(l);
    // 申请一块totalsize大小的内存，并转换为GCObject*，目的是为了赋值marked和tt
	o = luaC_newobj(L, tag, totalsize);
    // 将GCObject指向的这块内存转换成TString指针
	ts = gco2ts(o);
	ts->hash = h;
	ts->extra = 0;
	getstr(ts)[l] = '\0';
	return ts;
}

static TString *internshrstr (lua_State *L, const char *str, size_t l)
{
	TString *ts;
	global_State *g = G(L);
	unsigned int h = l_hash(str, l, g->seed);
	TString **list = &g->strt.hash[lmod(h, g->strt.size)];
	l_assert(str != NULL);
    // 放入字符串之前，先查看有没有相同的字符串，有直接返回，否则创建新的
	for (ts = *list; ts != NULL; ts = ts->u.hnext) {
		if (l == ts->shrlen && (memcmp(str, getstr(ts), l * sizeof(char)) == 0)) {
			return ts;
		}
	}
	if (g->strt.nuse >= g->strt.size && g->strt.size <= MAX_INT/2) {
		l_resize(L, g->strt.size * 2);
		list = &g->strt.hash[lmod(h, g->strt.size)];
	}
	ts = createstrobj(L, l, TSHRSTR, h);
	memcpy(getstr(ts), str, l * sizeof(char));
	ts->shrlen = cast_byte(l);
	// *list是对应hash位置上的TString*列表首地址
	// 然后将新创建的ts的下个元素指向原来第一个TString
	ts->u.hnext = *list;
	// 将原来的第一个元素指向新创建的ts
	*list = ts;
	g->strt.nuse++;
	return ts;
}

TString *l_createlngstrobj (lua_State *L, size_t l)
{
	TString *ts = createstrobj(L, l, TLNGSTR, G(L)->seed);
	ts->u.lnglen = l;
	return ts;
}

TString * l_newlstr (lua_State *L, const char *str, size_t l)
{
	if (l <= 40) {
		return internshrstr(L, str, l);
	}
	else {
		TString *ts = l_createlngstrobj(L, l);
		memcpy(getstr(ts), str, l * sizeof(char));
		return ts;
	}
}
//#define TEST_5
#ifdef TEST_5

static void dump_strt (lua_State *L)
{
    int i;
    global_State *g = G(L);
    for (i = 0; i < g->strt.size; i++) {
        if (g->strt.hash[i]) {
            TString *str = g->strt.hash[i];
            char buff[40];
            // 存储的时候加了个sizeof(struct UTString)对齐，取的时候要从对齐之后取字符
            // 并且lua字符串和c字符串不同，当转换为c字符串时，要添加结束符
            // memcpy(buff, getstr(str), str->shrlen);
            // buff[str->shrlen] = '\0';
            // 实际上createstrobj时，字符串已经加上了'\0'，但是需要多加一个字节去取
            memcpy(buff, getstr(str), str->shrlen+1);
            printf("%s %d\n", buff, str->shrlen);
            // 如果冲突，则根据首地址以及hnext获取下个存储的位置
        }
    }
}

int main (int argc, char const *argv[])
{
	lua_State *L = l_newstate();
	l_sinit(L);
	TString *str1 = l_newlstr(L, "a", 1);
	TString *str2 = l_newlstr(L, "ab", 2);
	TString *str3 = l_newlstr(L, "abc", 3);
	TString *str4 = l_newlstr(L, "abcd", 4);
	TString *str5 = l_newlstr(L, "abcde", 5);
    (void)str1;
    (void)str2;
    (void)str3;
    (void)str4;
    (void)str5;
    dump_strt(L);
    
    GCObject * o = luaC_newobj(L, TSHRSTR, 2);
    printf("gco tt = %d, marked = %d\n", o->tt, o->marked);
    TString *ts = gco2ts(o);
    printf("ts tt = %d, marked = %d\n", ts->tt, ts->marked);

    // @todo 长字符串存储
    
	return 0;
}
#endif
