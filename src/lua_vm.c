#include "lua_vm.h"
#include "log.h"
#include "window.h"
#include "lua_shared.h"

static lua_State *lua_state = NULL;


int lua_start(){
    if(!lua_state){
        lua_state = luaL_newstate();

        if(!lua_state){
            DWARN("Lua Interpreter Failed to Load!");
            window_exit();
            return 0;
        }
    }
    luaL_openlibs(lua_state);
    return 1;
}


void lua_end(lua_State *l){
    if(l != NULL){
        lua_close(l);
        l = NULL;
        return;
    }

    return;
}


int lua_check(lua_State *L, int res)
{
    if(L == NULL) {
        DWARN("Lua Script Error: Lua VM is (null)");
        return -1;
    }

    if(res != LUA_OK){
       DWARN("Lua Error: %s",  lua_tostring(L, -1));
       return lua_error(L);
    }
    return -1;
}


int  lua_exec_script_name(lua_State *L, const char *filepath, const char *func_name, void *host)
{
    if(lua_check(L, luaL_dofile(L, filepath)) < 0){
        lua_getglobal(L, func_name);

        if(lua_isfunction(L, -1)){
            lua_pushlightuserdata(L, host);

            if(lua_check(L, lua_pcall(L, 1,1,0)) < 0 || lua_check(L, lua_pcall(L, 1,1,0))  == LUA_ERRRUN){
                return 1;
            }
        }
    }

    return 0;
}

int lua_exec(lua_State *L, const char *filepath, void *host)
{
    return lua_exec_script_name(L, filepath, "init", host);
}


lua_State *lua_get_state()
{
    return lua_state;
}

void lua_free()
{
    lua_end(lua_state);
    return;
}
