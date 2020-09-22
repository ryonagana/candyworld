#ifndef LUA_SHARED_H
#define LUA_SHARED_H
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int lua_shared_register(lua_State *L);

#endif // LUA_SHARED_H
