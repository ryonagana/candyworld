#include "lua_vm.h"
#include "lua_hud.h"
#include "hud.h"
#include "log.h"
#include "window.h"

static int lua_hud_create(lua_State *L)
{
    if(lua_gettop(L) != 5) {
        return luaL_error(L, "this function expects 5 parameters");
    }


    int x = lua_tointeger(L, 2);
    int y = lua_tointeger(L, 3);

    int w = lua_tointeger(L,4);
    int h = lua_tointeger(L,5);

    hud_t *tmp = lua_touserdata(L, 1);
    tmp->x = x;
    tmp->y = y;
    tmp->height = w;
    tmp->width =  h;


    DINFO("script hud.lua loaded X:%d Y: %d W: %d H: %d", x,y,w,h);
    return LUA_OK;

}

static int lua_hud_set_lives_position(lua_State *L)
{
        if(lua_gettop(L) != 3) return -1;

        hud_t *hud = lua_touserdata(L, 1);

        int x = lua_tointeger(L, 2);
        int y = lua_tointeger(L, 3);

        hud->lives_x = x;
        hud->lives_y = y;

        return LUA_OK;
}

int lua_hud_register(lua_State *l, void *parent)
{
    if(l == NULL || parent == NULL) return 0;

    lua_register(l, "_createHud", lua_hud_create);
    lua_register(l, "_setLivesPosition", lua_hud_set_lives_position);

    lua_exec(l, "resources//scripts//hud.lua", parent);
    //lua_exec(l, "resources//scripts//test.lua", parent);
    return 1;
}
