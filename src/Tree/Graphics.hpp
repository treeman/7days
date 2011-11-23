#pragma once

#include <SFML/Graphics.hpp>

#include "Rect.hpp"

namespace Tree
{
    void Draw( const sf::Drawable &obj );

    bool IsVisible( const Tree::Rect &r );

    //mostly for lazy drawing
    void Redraw();
    void Redraw( const Tree::Rect &rect );
    void ClearWindow( sf::Color col = sf::Color() );
    bool NeedRedraw();

    void DrawLazy();
    void DrawNonLazy();
    bool DrawingLazy();

    void NeverClear();
    void SetClear();

    class Color {
    public:
        Color();
        Color( unsigned long color );
        Color( sf::Color color );

        operator sf::Color() const;
        unsigned long Hex() const;

        bool operator == ( const Color &c );
        bool operator != ( const Color &c );

        unsigned int r, g, b, a;
    };

    Color linear( Color start, Color end, float percent );
    Color normalize( Color start, Color end, float percent );

    inline std::ostream &operator << ( std::ostream &o, const Color &c )
    {
        sf::Color col = c;
        return o << col.a <<","<< col.r <<","<< col.g <<","<< col.b << '\n';
    }
}

