#include "Butler.hpp"
#include "PixFont.hpp"

PixFont::PixFont( std::string image, int w, int h, int space ) :
    char_w( w ), char_h( h ), char_space( space )
{
    Tree::ImgPtr img = BUTLER->GetImage( image );

    for( int n = 0; n < 26; ++n ) {
        SetBox( img.get(), n, 'A' + n );
    }

    for( int n = 0; n < 10; ++n ) {
        SetBox( img.get(), n + 26, '0' + n );
    }

    SetBox( img.get(), 36, '.' );
    SetBox( img.get(), 37, '!' );
    SetBox( img.get(), 38, '?' );
    SetBox( img.get(), 39, ' ' );
    SetBox( img.get(), 40, '=' );
    SetBox( img.get(), 41, '$' );
}

int PixFont::GetWidth() const
{
    return 3;
}
int PixFont::GetSpace() const
{
    return 1;
}

sf::Sprite PixFont::Get( char ch )
{
    SprMap::iterator it = chars.find( ch );
    if( it != chars.end() ) {
        return it->second;
    }
    else {
        return chars[' '];
    }
}

void PixFont::SetBox( sf::Image *img, int n, int ch )
{
    sf::Sprite spr;
    spr.SetImage( *img );

    const int x1 = char_space + n * (char_w + char_space);
    const int y1 = 0;
    const int x2 = x1 + char_w;
    const int y2 = char_h;

    spr.SetSubRect( sf::IntRect( x1, y1, x2, y2 ) );
    chars.insert( std::make_pair( ch, spr ) );
}

String::String() : fnt( 0 )
{

}

void String::SetPos( Vec2i _pos )
{
    pos = _pos;
}
void String::SetPos( int x, int y )
{
    pos.x = x; pos.y = y;
}

Vec2i String::GetPos()
{
    return pos;
}

void String::SetFont( PixFont &f )
{
    fnt = &f;
}
void String::SetText( std::string s )
{
    txt = s;
}
void String::SetColor( Tree::Color col )
{
    color = col;
}

String::Sprites String::GetSprites()
{
    String::Sprites sprs;

    if( fnt ) {
        const int w = fnt->GetWidth();
        const int space = fnt->GetSpace();

        for( size_t i = 0; i < txt.size(); ++i ) {
            char ch = toupper( txt[i] );

            sf::Sprite spr = fnt->Get( ch );
            spr.SetPosition( pos.x + i * ( w + space ), pos.y );
            spr.SetColor( color );

            sprs.push_back( spr );
        }
    }

    return sprs;
}

