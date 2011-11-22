#pragma once

#include "Tree/All.hpp"

class PixSpr {
public:
    virtual ~PixSpr() { }

    typedef std::vector<sf::Sprite> Sprites;
    virtual Sprites GetSprites() = 0;
};

