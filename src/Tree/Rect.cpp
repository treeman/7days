#include "Rect.hpp"

using Tree::Rect;

Rect::Rect( float x, float y, float width, float height, bool is_centered )
{
    Set( x, y, width, height, is_centered );
}
Rect::Rect( sf::FloatRect r )
{
    SetAnchors( r.Left, r.Top, r.Right, r.Bottom );
}

void Rect::Set( float x, float y, float width, float height, bool is_centered )
{
    x1 = x; y1 = y;
    x2 = x + width;
    y2 = y + height;
}
void Rect::SetAnchors( float _x1, float _y1, float _x2, float _y2 )
{
    x1 = _x1; y1 = _y1;
    x2 = _x2; y2 = _y2;
}

void Rect::SetPos( float x, float y )
{
    x2 = x2 - x1 + x;
    y2 = y2 - y1 + y;
    x1 = x;
    y1 = y;
}

bool Rect::IsOver( const Vec2f &pos ) const
{
    return IsOver( pos.x, pos.y );
}
bool Rect::IsOver( float x, float y ) const
{
    return  x > x1 && x < x2 &&
            y > y1 && y < y2;
}

bool Rect::Intersects( const Rect &rect ) const
{
    const float min_x = std::max( x1, rect.x1 );
    const float min_y = std::max( y1, rect.y1 );
    const float max_x = std::min( x2, rect.x2 );
    const float max_y = std::min( y2, rect.y2 );

    return min_x < max_x && min_y < max_y;
}

Vec2f Rect::GetCenter() const
{
    return Vec2f( x1 + ( x2 - x1 ) / 2, y1 + ( y2 - y1 ) / 2 );
}

