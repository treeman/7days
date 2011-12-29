#pragma once

#include <vector>
#include <string>
#include <map>
#include <sstream>

#include <boost/shared_ptr.hpp>
#include <SFML/Window.hpp>

#include "Vec2D.hpp"

// Easy access to elements
#define BUTLER Tree::get_butler()
#define TWEAKS Tree::get_tweaks()
#define SETTINGS Tree::get_settings()

// Easy debug
#define D_ Tree::debug
#define DP_ Tree::debug_persist

/*
 * You can do
 *
 * Tree::debug( "running function" )
 * Tree::debug( "%d + %d = %d", 2, 2, 4 )
 * D_( "If you're lazy" )
 * D_( "I R %.3f", 1.337 );
 *
 * And if there's a value you only sometime have but things are
 * too fast for you to see
 *
 * Tree::debug_persistent( "calc", "c = %d", 2 );
 * DP_( "calc", "c = %d", 3 )
 *
 * Remove with
 *
 * Tree::debug_remove( "calc" )
 */

#define WINDOW_WIDTH Tree::get_window_width()
#define WINDOW_HEIGHT Tree::get_window_height()

#define MAGIC_NUM(name) TWEAKS->GetNum( name )
#define MAGIC_STRING(name) TWEAKS->GetString( name )

// Make life easier
typedef std::vector<std::string> Strings;
typedef std::map<std::string, std::string> StringMap;

namespace Tree
{
    // A bunch of helper functions who fetch states from game
    extern float get_FPS();
    extern const sf::Input &get_input();

    extern const int get_window_width();
    extern const int get_window_height();

    extern bool is_mouse_valid();
    extern Vec2f get_mouse_pos();
    extern void set_mouse_pos( const Vec2f &pos );
    extern void set_mouse_pos( float x, float y );

    extern void exit();

    // Debug stuff and print on screen every frame
    extern void debug( std::string str );
    extern void debug( const char *msg, ... );

    // Persistent debug, no need to set every frame
    extern void debug_persist( std::string id, std::string str );
    extern void debug_persist( std::string id, const char *msg, ... );

    // Remove persistent debug val
    extern void debug_remove( std::string id );

    // Set a key for event logging
    extern void set_log_key( int key );
    // Is log key pressed? Don't spam the log
    extern bool shall_log();

    // Request at least this version of the library
    extern void request_version( float version );

    class Butler;
    class Settings;
    class Tweaks;
    class LogHelper;

    // Get classes from game
    boost::shared_ptr<Tree::Butler> get_butler();
    boost::shared_ptr<Tree::Settings> get_settings();
    boost::shared_ptr<Tree::Tweaks> get_tweaks();
    boost::shared_ptr<Tree::LogHelper> get_log_helper();
}

