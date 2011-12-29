#pragma once

#include <SFML/Graphics.hpp>

#include "Rect.hpp"

namespace Tree
{
    void draw( const sf::Drawable &obj );

    bool is_visible( const Tree::Rect &r );

    // Mostly for lazy drawing
    void redraw();
    void redraw( const Tree::Rect &rect );
    void clear_window( sf::Color col = sf::Color() );
    bool need_redraw();

    void draw_lazy();
    void draw_non_lazy();
    bool drawing_lazy();

    void never_clear();
    void set_clear();

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

    std::ostream &operator << ( std::ostream &o, const Color &c );

    void set_alpha( sf::Sprite &spr, int a );

    // Drawing of simple symbols.
    void draw_line(
        float x1, float y1, float x2, float y2,
        const Color &col, float thickness = 1.0,
        const Color &outline_col = Color::clear, float outline = 0.f
    );
    void draw_line(
        Vec2f p1, Vec2f p2,
        const Color &col, float thickness = 1.0,
        const Color &outline_col = Color::clear, float outline = 0.f
    );

    void draw_triangle(
        float x1, float y1, float x2, float y2, float x3, float y3, const Color &col,
        const Color &outline_col = Color::clear, float outline = 0.f
    );
    void draw_triangle(
        Vec2f p1, Vec2f p2, Vec2f p3, const Color &col,
        const Color &outline_col = Color::clear, float outline = 0.f
    );

    void draw_rect(
        float x1, float y1, float x2, float y2, const Color &col,
        const Color &outline_col = Color::clear, float outline = 0.f
    );
    void draw_rect(
        Vec2f p1, Vec2f p2, const Color &col,
        const Color &outline_col = Color::clear, float outline = 0.f
    );

    void draw_circle(
        float x, float y, float rad, const Color &col,
        const Color &outline_col = Color::clear, float outline = 0.f
    );
    void draw_circle(
        Vec2f center, float rad, const Color &col,
        const Color &outline_col = Color::clear, float outline = 0.f
    );

    // Draw horisontal status bar
    // x1,y1 top left and x2,y2 bottom right
    void draw_bar(
        float x1, float y1, float x2, float y2, float perc,
        const Color &bg_col, const Color &fg_col,
        const Color &outline_col = Color::clear, float outline = 0.f
    );
    void draw_bar(
        Vec2f p1, Vec2f p2, float perc,
        const Color &bg_col, const Color &fg_col,
        const Color &outline_col = Color::clear, float outline = 0.f
    );
}

