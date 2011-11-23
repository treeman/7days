#pragma once

#include <boost/unordered_set.hpp>

#include "Graphics.hpp"

#include "PixSpr.hpp"

class PixMap {
public:
    PixMap();

    void SetPix( Vec2i point, Tree::Color col );
    void SetPix( int x, int y, Tree::Color col );

    Tree::Color GetPix( Vec2i point );
    Tree::Color GetPix( int x, int y );

    int Width() const;
    int Height() const;

    void Draw( sf::Sprite spr );
    void Draw( PixSpr *const spr );

    void Draw();
    void Redraw();
private:
    typedef std::vector<Tree::Color> PixRow;
    typedef std::vector<PixRow> Pix2D;
    Pix2D pixels;
    Pix2D next;

    typedef boost::unordered_set<Vec2i> Points;
    Points points_to_update;

    sf::Sprite mask;

    size_t width, height;
    size_t pix_width;
};

