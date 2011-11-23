#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include "Demo.hpp"

Demo::Demo()
{
    Tree::GetTweaks()->Load( "magic_numbers.lua" );

    str = BUTLER->CreateString( "fnt/arial.ttf", 60 );
    str.SetColor( Tree::Color( 0xFFC989C7 ) );
    str.SetText( "Hello World!" );
    str.SetPosition( 300, 200 );
}

void Demo::Draw()
{
    Tree::ClearWindow( Tree::Color( 0xFF89C98B ) );
    Tree::Draw( str );
}

