#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

void print_hex(const char * desc, int d)
{
	printf("%s: 0x%x\n", desc, d);
}

int main(int argc, char const *argv[])
{

	const char *file = "test.lua";
	lua_State *L = luaL_newstate();
	luaL_dofile(L, file);

	return 0;
}