#pragma once

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Singleton.hpp"
#include "Exceptions.hpp"
#include "Sprite.hpp"
#include "Util.hpp"

namespace Tree
{
    typedef boost::shared_ptr<sf::Font> FntPtr;
    typedef boost::shared_ptr<sf::Image> ImgPtr;
    typedef boost::shared_ptr<sf::SoundBuffer> SndPtr;

    class Butler {
    public:
        Butler();
        ~Butler();

        void LoadSprites( std::string lua_file );

        // Create direct resources
        FntPtr GetFont( std::string path, unsigned int size = 30 )
            throw( Tree::resource_load_error );
        ImgPtr GetImage( std::string path, bool shall_smooth = false )
            throw( Tree::resource_load_error );
        SndPtr GetSoundBuffer( std::string path )
            throw( Tree::resource_load_error );

        // Create throw-away handlers
        sf::Sprite CreateSprite( std::string name )
            throw( Tree::resource_load_error );
        sf::Sprite CreateSprite( std::string img_path, int index,
            int width, int height ) throw( Tree::resource_load_error );
        sf::Sprite CreateSprite( const sf::Image &image, int index,
            int width, int height ) throw( Tree::resource_load_error );

        sf::String CreateString( std::string fnt_path, int size )
            throw( Tree::resource_load_error );
        sf::Sound CreateSound( std::string snd_path )
            throw( Tree::resource_load_error );
    private:
        SpriteLoader spr_loader;

        typedef std::multimap<std::string, FntPtr> FontMap;
        FontMap font_map;

        typedef std::map<std::string, ImgPtr> ImageMap;
        ImageMap image_map;

        typedef std::map<std::string, SndPtr> SoundMap;
        SoundMap sound_map;
    };
}

