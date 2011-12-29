#include <boost/lexical_cast.hpp>
#include <sstream>

#include "GameDebug.hpp"
#include "Butler.hpp"
#include "Util.hpp"
#include "Vec2D.hpp"
#include "Tweaks.hpp"
#include "Graphics.hpp"
#include "Log.hpp"

using Tree::GameDebug;

GameDebug::GameDebug()
{
    show_mouse_pos.reset( new Dator<bool>( false ) );
    SETTINGS->RegisterVariable( "mouse_pos_show",
        boost::weak_ptr<BaseDator>( show_mouse_pos ) );

    show_fps.reset( new Dator<bool>( false ) );
    SETTINGS->RegisterVariable( "fps_show",
        boost::weak_ptr<BaseDator>( show_fps ) );

    fps = BUTLER->CreateString( "fnt/lucon.ttf", 20 );
    fps.SetColor( Tree::Color( TWEAKS->GetNum( "font_debug_color" ) ) );
    fps.SetPosition( 5, 3 );

    mpos = BUTLER->CreateString( "fnt/consola.ttf", 10 );
    mpos.SetColor( Tree::Color( TWEAKS->GetNum( "font_debug_color" ) ) );
    mpos.SetPosition( 50, 7 );

    // Placeholder mouse pointer
    // doesn't matter if we find it or not
    try {
        mptr = BUTLER->CreateSprite( "gfx/ptr.png" );
    }
    catch( Tree::resource_load_error &e ) { }
}

bool GameDebug::HandleEvent( sf::Event &e )
{
    return true;
}

void GameDebug::Update( float )
{
    int my_fps = Tree::get_FPS();

    const std::string s = boost::lexical_cast<std::string>( my_fps );
    const std::string old_s = fps.GetText();
    fps.SetText( s );

    Vec2f mouse_pos = Tree::get_mouse_pos();
    mptr.SetPosition( mouse_pos );
    std::stringstream ss;
    ss << mouse_pos.x << "," << mouse_pos.y;
    mpos.SetText( ss.str() );
}
void GameDebug::Render()
{
    // Will not really work with lazy drawing!
    if( show_fps->Val() ) {
        Tree::draw( fps );
    }
    if( show_mouse_pos->Val() ) {
        Tree::draw( mpos );
        Tree::draw( mptr );
    }
}

