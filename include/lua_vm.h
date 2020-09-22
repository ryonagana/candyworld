#ifndef LUA_VM_HEADER
#define LUA_VM_HEADER
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>



int lua_start();
void lua_end(lua_State *l);
lua_State *lua_get_state();
void lua_free();

int lua_exec_script_name(lua_State *L, const char *filepath, const char *func_name, void *host);
int lua_exec(lua_State *L, const char *filepath, void *host);
#endif
