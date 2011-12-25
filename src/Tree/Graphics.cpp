#include <algorithm>

#include "Graphics.hpp"
#include "Game.hpp"

void Tree::Draw( const sf::Drawable &obj )
{
    GAME->Draw( obj );
}

bool Tree::IsVisible( const Tree::Rect &r )
{
    return ( r.x2 > 0 && r.x1 < Tree::GetWindowWidth() )
        || ( r.y2 > 0 && r.y1 < Tree::GetWindowHeight() );
}

void Tree::Redraw()
{
    Tree::ClearWindow();
}
void Tree::Redraw( const Tree::Rect &rect )
{
    GAME->PortionRedrawn( rect );
}

void Tree::ClearWindow( sf::Color col )
{
    GAME->ClearWindow( col );
}
bool Tree::NeedRedraw()
{
    return GAME->NeedRedraw();
}

void Tree::DrawLazy()
{
    GAME->DrawLazy();
}
void Tree::DrawNonLazy()
{
    GAME->DrawNormal();
}
bool Tree::DrawingLazy()
{
    return GAME->DrawingLazy();
}

void Tree::NeverClear()
{
    GAME->NeverClear();
}
void Tree::SetClear()
{
    GAME->SetClear();
}

using Tree::Color;

const Color Color::clear( 0, 0, 0, 0 );
const Color Color::black( 0, 0, 0 );
const Color Color::white( 255, 255, 255 );

const Color Color::red( 255, 0, 0 );
const Color Color::green( 0, 255, 0 );
const Color Color::blue( 0, 0, 255 );

const Color Color::yellow( 255, 255, 0 );
const Color Color::magenta( 255, 0, 255 );
const Color Color::cyan( 0, 255, 255 );

Color::Color() : a(255), r(255), g(255), b(255)
{
}
Color::Color( int _r, int _g, int _b ) : a(255), r(_r), g(_g), b(_b)
{
}
Color::Color( int _a, int _r, int _g, int _b ) : a(_a), r(_r), g(_g), b(_b)
{
}
Color::Color( unsigned long col )
{
    a = col >> 24;
    r = (col >> 16) & 0xFF;
    g = (col >> 8) & 0xFF;
    b = col & 0xFF;
}
Color::Color( sf::Color col )
{
    a = col.a;
    r = col.r;
    g = col.g;
    b = col.b;
}

Color::operator sf::Color() const
{
    sf::Color color( r, g, b, a );
    return color;
}

unsigned long Color::Hex() const
{
    unsigned long col = 0;
    col = col | (a << 24);
    col = col | (r << 16);
    col = col | (g << 8);
    col = col | b;
    return col;
}

Color &Color::operator += ( const Color &c )
{
    a = std::min<int>( a + c.a, 255 );
    r = std::min<int>( r + c.r, 255 );
    g = std::min<int>( g + c.g, 255 );
    b = std::min<int>( b + c.b, 255 );

    return *this;
}
Color &Color::operator *= ( const Color &c )
{
    a = a * c.a / 255;
    r = r * c.r / 255;
    g = g * c.g / 255;
    b = b * c.b / 255;

    return *this;
}
bool Color::operator == ( const Color &c )
{
    return a == c.a && r == c.r &&
           g == c.g && b == c.b;
}
bool Color::operator != ( const Color &c )
{
    return !(*this == c);
}

Color operator + ( const Color &c1, const Color &c2 )
{
    Color c = c1;
    c += c2;
    return c;
}
Color operator * ( const Color &c1, const Color &c2 )
{
    Color c = c1;
    c *= c2;
    return c;
}

Color Tree::linear( const Color &start, const Color &end, float percent )
{
    Color result;
    result.a = start.a * ( 1.0f - percent ) + end.a * percent;
    result.r = start.r * ( 1.0f - percent ) + end.r * percent;
    result.g = start.g * ( 1.0f - percent ) + end.g * percent;
    result.b = start.b * ( 1.0f - percent ) + end.b * percent;
    return result;
}

Color Tree::normalize( const Color &start, const Color &end, float percent )
{
    float start_length = std::sqrt( start.r * start.r +
                                    start.g * start.g +
                                    start.b * start.b );

    float end_length = std::sqrt( end.r * end.r +
                                  end.g * end.g +
                                  end.b * end.b );

    float length = start_length * ( 1.0f - percent ) + end_length * percent;

    Color result;
    result.r = start.r * ( 1.0f - percent ) + end.r * percent;
    result.g = start.g * ( 1.0f - percent ) + end.g * percent;
    result.b = start.b * ( 1.0f - percent ) + end.b * percent;

    float cur_length = sqrt ( result.r * result.r +
                              result.g * result.g +
                              result.b * result.b );

    float ratio = length / cur_length;

    result.r *= ratio;
    result.g *= ratio;
    result.b *= ratio;

    return result;
}

void Tree::DrawLine(
    float x1, float y1, float x2, float y2, const Color &col, float thickness,
    const Color &outline_col, float outline
)
{
    Tree::Draw( sf::Shape::Line( x1, y1, x2, y2,
        thickness, col, outline, outline_col ) );
}
void Tree::DrawLine(
    Vec2f p1, Vec2f p2, const Color &col, float thickness,
    const Color &outline_col, float outline
)
{
    Tree::Draw( sf::Shape::Line( p1, p2, thickness, col, outline, outline_col ) );
}

void Tree::DrawTriangle(
    float x1, float y1, float x2, float y2, float x3, float y3,
    const Color &col, const Color &outline_col, float outline
)
{
    DrawTriangle(
        Vec2f( x1, y1 ), Vec2f( x2, y2 ), Vec2f( x3, y3 ),
        col, outline_col, outline
    );
}
void Tree::DrawTriangle(
    Vec2f p1, Vec2f p2, Vec2f p3,
    const Color &col, const Color &outline_col, float outline
)
{
    sf::Shape s;
    s.AddPoint( p1, col, outline_col );
    s.AddPoint( p2, col, outline_col );
    s.AddPoint( p3, col, outline_col );

    s.SetOutlineWidth( outline );
    Tree::Draw( s );
}

void Tree::DrawRect(
    float x1, float y1, float x2, float y2, const Color &col,
    const Color &outline_col, float outline
)
{
    Tree::Draw( sf::Shape::Rectangle( x1, y1, x2, y2, col, outline, outline_col ) );
}
void Tree::DrawRect(
    Vec2f p1, Vec2f p2, const Color &col,
    const Color &outline_col, float outline
)
{
    Tree::Draw( sf::Shape::Rectangle( p1, p2, col, outline, outline_col ) );
}

void Tree::DrawCircle(
    float x, float y, float rad, const Color &col,
    const Color &outline_col, float outline
)
{
    Tree::Draw( sf::Shape::Circle( x, y, rad, col, outline, outline_col ) );
}
void Tree::DrawCircle(
    Vec2f center, float rad, const Color &col,
    const Color &outline_col, float outline
)
{
    Tree::Draw( sf::Shape::Circle( center, rad, col, outline, outline_col ) );
}

void Tree::DrawBar(
    float x1, float y1, float x2, float y2, float perc,
    const Color &bg_col, const Color &fg_col,
    const Color &outline_col, float outline
)
{
    if( perc > 1.0 ) perc = 1.0;
    if( perc < 0 ) perc = 0.0;

    const int w = std::abs( x1 - x2 );
    const int filled = w * perc;

    // Background + outline
    Tree::DrawRect( x1, y1, x2, y2, bg_col, outline_col, outline );

    // Filled
    Tree::DrawRect( x1, y1, x1 + filled, y2, fg_col );
}
void Tree::DrawBar(
    Vec2f p1, Vec2f p2, float perc, const Color &bg_col, const Color &fg_col,
    const Color &outline_col, float outline
)
{
    DrawBar( p1.x, p1.y, p2.x, p2.y, perc, bg_col, fg_col, outline_col, outline );
}

