#include "Butler.hpp"
#include "Util.hpp"
#include "VisualDebug.hpp"
#include "Tweaks.hpp"
#include "Graphics.hpp"
#include "Log.hpp"
#include "Settings.hpp"

using Tree::VisualDebug;

VisualDebug::VisualDebug() :
    x_pos( WINDOW_WIDTH - 5 ),
    y_pos( 7 ),
    line_height( 12 )
{
    render_str = BUTLER->CreateString( "fnt/consola.ttf", 10 );
    render_str.SetColor( Tree::Color( TWEAKS->GetNum( "font_debug_color" ) ) );

    SETTINGS->Register( "visual_debug_show", false );
}

void VisualDebug::Add( std::string s )
{
    temp.push_back( s );
}
void VisualDebug::SetPersistent( std::string id, std::string s )
{
    RemovePersistent( id );
    persistent.insert( std::make_pair( id, s ) );
}
void VisualDebug::RemovePersistent( std::string id )
{
    StringMap::iterator it = persistent.find( id );
    if( it != persistent.end() ) {
        persistent.erase( persistent.find( id ) );
    }
}

void VisualDebug::ResetTempStrings()
{
    temp.clear();
}
void VisualDebug::Render()
{
    // We shouldn't show anything
    if( !SETTINGS->GetValue<bool>( "visual_debug_show" ) ) {
        return;
    }

    int i = 0;
    for( StringMap::iterator it = persistent.begin();
         it != persistent.end(); ++it, ++i )
    {
        render_str.SetText( it->second );
        render_str.SetPosition( x_pos - render_str.GetRect().GetWidth(),
            y_pos + i * line_height );
        Tree::draw( render_str );
    }

    for( Strings::iterator it = temp.begin();
         it != temp.end(); ++it, ++i )
    {
        render_str.SetText( *it );
        render_str.SetPosition( x_pos - render_str.GetRect().GetWidth(),
            y_pos + i * line_height );
        Tree::draw( render_str );
    }
}

