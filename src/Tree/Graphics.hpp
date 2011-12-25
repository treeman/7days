#pragma once

#include <SFML/Graphics.hpp>

#include "Rect.hpp"

namespace Tree
{
    void Draw( const sf::Drawable &obj );

    bool IsVisible( const Tree::Rect &r );

    // Mostly for lazy drawing
    void Redraw();
    void Redraw( const Tree::Rect &rect );
    void ClearWindow( sf::Color col = sf::Color() );
    bool NeedRedraw();

    void DrawLazy();
    void DrawNonLazy();
    bool DrawingLazy();

    void NeverClear();
    void SetClear();

    // Utility class. Transparent with sf::Color
    // and allows for easy hex conversions.
    class Color {
    public:
        Color();
        Color( int r, int g, int b );
        Color( int a, int r, int g, int b );
        Color( unsigned long color );
        Color( sf::Color color );

        operator sf::Color() const;
        unsigned long Hex() const;

        Color &operator += ( const Color &c );
        Color &operator *= ( const Color &c );
        bool operator == ( const Color &c );
        bool operator != ( const Color &c );

        unsigned int a, r, g, b;

        // Names for common colors
        static const Color clear;
        static const Color black;
        static const Color white;

        static const Color red;
        static const Color green;
        static const Color blue;

        static const Color yellow;
        static const Color magenta;
        static const Color cyan;
    };

    Color operator + ( const Color &c1, const Color &c2 );
    Color operator * ( const Color &c1, const Color &c2 );

    Color linear( const Color &start, const Color &end, float percent );
    Color normalize( const Color &start, const Color &end, float percent );

    inline std::ostream &operator << ( std::ostream &o, const Color &c )
    {
        sf::Color col = c;
        return o << col.a <<","<< col.r <<","<< col.g <<","<< col.b << '\n';
    }

    // Drawing of simple symbols.
    void DrawLine(
        float x1, float y1, float x2, float y2,
        const Color &col, float thickness = 1.0,
        const Color &outline_col = Color::clear, float outline = 0.f
    );
    void DrawLine(
        Vec2f p1, Vec2f p2,
        const Color &col, float thickness = 1.0,
        const Color &outline_col = Color::clear, float outline = 0.f
    );

    void DrawTriangle(
        float x1, float y1, float x2, float y2, float x3, float y3, const Color &col,
        const Color &outline_col = Color::clear, float outline = 0.f
    );
    void DrawTriangle(
        Vec2f p1, Vec2f p2, Vec2f p3, const Color &col,
        const Color &outline_col = Color::clear, float outline = 0.f
    );

    void DrawRect(
        float x1, float y1, float x2, float y2, const Color &col,
        const Color &outline_col = Color::clear, float outline = 0.f
    );
    void DrawRect(
        Vec2f p1, Vec2f p2, const Color &col,
        const Color &outline_col = Color::clear, float outline = 0.f
    );

    void DrawCircle(
        float x, float y, float rad, const Color &col,
        const Color &outline_col = Color::clear, float outline = 0.f
    );
    void DrawCircle(
        Vec2f center, float rad, const Color &col,
        const Color &outline_col = Color::clear, float outline = 0.f
    );

}

