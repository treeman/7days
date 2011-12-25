#pragma once

#include "Tree.hpp"

class Demo : public Tree::GameState {
public:
    Demo();

    bool HandleEvent( sf::Event &e );

    void Update( float dt );
    void Draw();
private:
    sf::String str;
    int count;
};

