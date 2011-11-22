#pragma once

#include "Tree/All.hpp"

#include "PixMap.hpp"

// A simple pixelated font
class PixFont {
public:
    PixFont( std::string image, int w, int h, int space );

    int GetWidth() const;
    int GetSpace() const;

    sf::Sprite Get( char ch );
private:
    typedef std::map<int, sf::Sprite> SprMap;
    SprMap chars;

    int char_w, char_h, char_space;

    void SetBox( sf::Image *img, int n, int ch_code );
};

class String : public PixSpr {
public:
    String();

    void SetPos( Vec2i pos );
    void SetPos( int x, int y );

    Vec2i GetPos();

    void SetFont( PixFont &fnt );
    void SetText( std::string txt );
    void SetColor( Tree::Color col );

    Sprites GetSprites();
private:
    std::string txt;
    Vec2i pos;
    Tree::Color color;

    PixFont * fnt;
};

