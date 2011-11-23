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
    Tree::GetSettings()->RegisterVariable( "mouse_pos_show",
        boost::weak_ptr<BaseDator>( show_mouse_pos ) );

    show_fps.reset( new Dator<bool>( false ) );
    Tree::GetSettings()->RegisterVariable( "fps_show",
        boost::weak_ptr<BaseDator>( show_fps ) );

    fps = Tree::GetButler()->CreateString( "fnt/lucon.ttf", 20 );
    fps.SetColor( Tree::Color( Tree::GetTweaks()->GetNum( "font_debug_color" ) ) );
    fps.SetPosition( 5, 3 );

    mpos = Tree::GetButler()->CreateString( "fnt/consola.ttf", 10 );
    mpos.SetColor( Tree::Color( Tree::GetTweaks()->GetNum( "font_debug_color" ) ) );
    mpos.SetPosition( 50, 7 );
}

bool GameDebug::HandleEvent( sf::Event &e )
{
    return true;
}

void GameDebug::Update( float )
{
    int my_fps = Tree::GetFPS();

    const std::string s = boost::lexical_cast<std::string>( my_fps );
    const std::string old_s = fps.GetText();
    fps.SetText( s );

    // Will not really work with lazy drawing!
    /*if( s != old_s ) {
        Tree::Redraw();
    }*/

    Vec2f mouse_pos = Tree::GetMousePos();
    std::stringstream ss;
    ss << mouse_pos.x << "," << mouse_pos.y;
    mpos.SetText( ss.str() );
}
void GameDebug::Render()
{
    if( show_fps->Val() ) {
        Tree::Draw( fps );
    }
    if( show_mouse_pos->Val() ) {
        Tree::Draw( mpos );
    }
}

