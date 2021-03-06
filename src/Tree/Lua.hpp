#pragma once

#include <lua.hpp>

namespace Tree
{
    class LuaState {
    public:
        LuaState() : L( lua_open() ) {
            luaL_openlibs( L );
        }

        ~LuaState() {
            lua_close( L );
        }
        //implicitly act as a lua_State pointer
        inline operator lua_State*() {
            return L;
        }

    protected:
        lua_State *L;
    };

    inline bool get_string( lua_State *L, std::string name, std::string &result )
    {
        bool success = false;

        lua_pushstring( L, name.c_str() );
        lua_gettable( L, -2 );
        if( lua_isstring( L, -1 ) ) {
            result = lua_tostring( L, -1 );
            success = true;
        }
        lua_pop( L, 1 );
        return success;
    }

    template<typename T>
    inline bool get_num( lua_State *L, std::string name, T &result )
    {
        bool success = false;

        lua_pushstring( L, name.c_str() );
        lua_gettable( L, -2 );
        if( lua_isnumber( L, -1 ) ) {
            result = static_cast<T>( lua_tonumber( L, -1 ) );
            success = true;
        }
        lua_pop( L, 1 );
        return success;
    }

    inline bool get_bool( lua_State *L, std::string name, bool &result )
    {
        bool success = false;

        lua_pushstring( L, name.c_str() );
        lua_gettable( L, -2 );
        if( lua_isboolean( L, -1 ) ) {
            result = lua_toboolean( L, -1 );
            success = true;
        }
        lua_pop( L, 1 );
        return success;
    }
}

