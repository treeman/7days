#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include "Demo.hpp"

Demo::Demo()
{
    str = BUTLER->CreateString( "fnt/arial.ttf", 60 );
    str.SetColor( Tree::Color( 0xFFCC4343 ) );
    str.SetText( "Hello World!" );
    str.SetPosition( 300, 200 );
}

void Demo::Draw()
{
    Tree::clear_window( Tree::Color( 0xFF89C98B ) );
    Tree::draw( str );
}

