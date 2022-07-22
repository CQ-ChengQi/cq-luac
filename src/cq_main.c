#include <stdio.h>
#include <string.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

static void stack_dump(lua_State *L)
{
    int i;
    int top = lua_gettop(L); // 栈的深度
    for (i = 1; i <= top; i++)
    {
        int t = lua_type(L, i);
        switch (t)
        {
        case LUA_TSTRING:
            printf("'%s'", lua_tostring(L, i));
            break;
        case LUA_TBOOLEAN:
            printf(lua_tostring(L, i) ? "true" : "false");
            break;
        case LUA_TNUMBER:
            printf("%g", lua_tonumber(L, i));
            break;
        default:
            printf("%s", lua_typename(L, t));
            break;
        }
        printf("  ");
    }
    printf("\n");
}

int main()
{

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // char buff[256];
    // int error;
    // while (fgets(buff, sizeof(buff), stdin) != NULL)
    // {
    //     error = luaL_loadstring(L, buff) || lua_pcall(L, 0, 0, 0);
    //     if (error)
    //     {
    //         fprintf(stderr, "%s\n", lua_tostring(L, -1));
    //         lua_pop(L, 1);
    //     }
    // }

    lua_pushboolean(L, 1);
    lua_pushnumber(L, 10);
    lua_pushnil(L);
    lua_pushstring(L, "hello");

    stack_dump(L);

    // lua_pushvalue(L, -1); // 将 -4 位置的值压入栈顶
    // stack_dump(L);

    lua_replace(L, 3);  // 将栈顶的值替换到 3 位置
    stack_dump(L);

    lua_close(L);
    return 0;
}