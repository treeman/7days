#include "Graphics.hpp"
#include "Game.hpp"

void Tree::Draw( const sf::Drawable &obj )
{
    GAME->Draw( obj );
}

bool Tree::IsVisible( const Tree::Rect &r )
{
    return r.x2 > 0 && r.y2 > 0;
        //&& r.x1 < Tree::GetWindowWidth()
        //&& r.y1 < Tree::GetWindowHeight();
    return false;
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

Color::Color()
{
    a = r = g = b = 255;
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

bool Color::operator == ( const Color &c )
{
    return a == c.a && r == c.r &&
           g == c.g && b == c.b;
}
bool Color::operator != ( const Color &c )
{
    return !(*this == c);
}

Color Tree::linear( Color start, Color end, float percent )
{
    Color result;
    result.a = start.a * ( 1.0f - percent ) + end.a * percent;
    result.r = start.r * ( 1.0f - percent ) + end.r * percent;
    result.g = start.g * ( 1.0f - percent ) + end.g * percent;
    result.b = start.b * ( 1.0f - percent ) + end.b * percent;
    return result;
}

Color Tree::normalize( Color start, Color end, float percent )
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

