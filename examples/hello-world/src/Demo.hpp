#pragma once

#include "Tree.hpp"

// Hello world!
class Demo : public Tree::GameState {
public:
    Demo();

    void Draw();
private:
    sf::String str;
    sf::Sprite background;
};

