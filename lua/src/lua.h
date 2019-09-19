#ifndef __LUA__
#define __LUA__

#include "luaconf.h"

typedef LUA_NUMBER lua_Number;
typedef LUA_INTEGER lua_Integer;

/*Lua 数据类型*/
// Lua栈可以使用索引存取值，当索引无效时对应的值为LUA_TNONE
#define LUA_TNONE				(-1)
#define LUA_TNIL				0
#define LUA_TBOOLEAN			1
#define LUA_TLIGHTUSERDATA		2 // void* 用户关注其生命周期
#define LUA_TNUMBER				3
#define LUA_TSTRING				4
#define LUA_TTABLE				5
#define LUA_TFUNCTION			6
#define LUA_TUSERDATA			7 // void* Lua关注其生命周期
#define LUA_TTHREAD				8

#endif /* __LUA__ */