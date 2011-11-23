#pragma once

// TODO what does this do?
class PixSpr {
public:
    virtual ~PixSpr() { }

    typedef std::vector<sf::Sprite> Sprites;
    virtual Sprites GetSprites() = 0;
};

