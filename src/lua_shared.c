#include "lua_shared.h"
#include "window.h"


static int lua_shared_getWidth(lua_State *L)
{
    if(lua_gettop(L) != 0) return -1;

    lua_pushinteger(L,window_get()->info.width);
    return 1;
}

static int lua_shared_getHeight(lua_State *L)
{
    if(lua_gettop(L) != 0) return -1;

    lua_pushinteger(L,window_get()->info.height);
    return 1;
}

static int lua_shared_getWindowSize(lua_State *L)
{
     if(lua_gettop(L) != 0) return -1;

     lua_pushinteger(L, window_get()->info.width);
     lua_pushinteger(L, window_get()->info.height);

     return 2;
}


int lua_shared_register(lua_State *L){

    if(L == NULL) return 0;

    lua_register(L, "_getWidth", lua_shared_getWidth);
    lua_register(L, "_getHeight", lua_shared_getHeight);
    lua_register(L, "_getWindowSize", lua_shared_getWindowSize);
    return 1;
}


