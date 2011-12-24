#pragma once

#include <vector>
#include <string>
#include <map>
#include <sstream>

#include <boost/shared_ptr.hpp>
#include <SFML/Window.hpp>

#include "Vec2D.hpp"

// Easy access to elements
#define BUTLER Tree::GetButler()
#define TWEAKS Tree::GetTweaks()
#define SETTINGS Tree::GetSettings()

// Easy debug
#define D_ Tree::Debug
#define DP_ Tree::DebugPersist

/*
 * You can do
 *
 * Tree::Debug( "running function" )
 * Tree::Debug( "%d + %d = %d", 2, 2, 4 )
 * D_( "If you're lazy" )
 * D_( "I R %.3f", 1.337 );
 *
 * And if there's a value you only sometime have but things are
 * too fast for you to see
 *
 * Tree::DebugPersistent( "calc", "c = %d", 2 );
 * DP_( "calc", "c = %d", 3 )
 *
 * Remove with
 *
 * Tree::DebugRemove( "calc" )
 */

#define WINDOW_WIDTH Tree::GetWindowWidth()
#define WINDOW_HEIGHT Tree::GetWindowHeight()

// Make life easier
typedef std::vector<std::string> Strings;
typedef std::map<std::string, std::string> StringMap;

namespace Tree
{
    // A bunch of helper functions who fetch states from game
    extern float GetFPS();
    extern const sf::Input &GetInput();

    extern const int GetWindowWidth();
    extern const int GetWindowHeight();

    extern bool IsMouseValid();
    extern Vec2f GetMousePos();
    extern void SetMousePos( const Vec2f &pos );
    extern void SetMousePos( float x, float y );

    // Debug stuff and print on screen every frame
    extern void Debug( std::string str );
    extern void Debug( const char *msg, ... );

    // Persistent debug, no need to set every frame
    extern void DebugPersist( std::string id, std::string str );
    extern void DebugPersist( std::string id, const char *msg, ... );

    // Remove persistent debug val
    extern void DebugRemove( std::string id );

    class Butler;
    class Settings;
    class Tweaks;
    class LogHelper;

    // Get classes from game
    boost::shared_ptr<Tree::Butler> GetButler();
    boost::shared_ptr<Tree::Settings> GetSettings();
    boost::shared_ptr<Tree::Tweaks> GetTweaks();
    boost::shared_ptr<Tree::LogHelper> GetLogHelper();
}

