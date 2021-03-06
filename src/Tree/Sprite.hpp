#pragma once

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>

#include "Lua.hpp"
#include "Exceptions.hpp"
#include "Graphics.hpp"
#include "Util.hpp"

namespace Tree
{
    // Manage sprites specified in a lua config file
    class SpriteLoader {
    public:
        SpriteLoader();

        // Different ways to load a file, either load it once or force a load
        // even if loaded before
        void Load( std::string lua_file ) throw( Tree::lua_error & );
        void ForceLoad( std::string lua_file ) throw( Tree::lua_error & );

        bool HasCustomSprite( std::string name );
        sf::Sprite Create( std::string name ) throw( Tree::resource_load_error & );
    private:
        typedef std::map<std::string, sf::Sprite> SpriteMap;
        SpriteMap sprite_map;
        Strings parsed_files;

        // Lua helper to load a sprite
        bool LoadSprite( lua_State *L, sf::Sprite *spr ) throw( Tree::lua_error & );
    };
}

