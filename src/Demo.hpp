#pragma once

#include "Tree/Graphics.hpp"
#include "Tree/GameState.hpp"
#include "Tree/Timer.hpp"
#include "Tree/Shufflebag.hpp"

//this demo tests some things :)
class Demo : public Tree::GameState {
public:
    Demo();

    bool HandleEvent( sf::Event &e );

    void Update( float dt );
    void Draw();
private:
    Tree::Timer t;
    Tree::Timer st;

    sf::String time_str;

    //testing the shufflebag
    boost::shared_ptr<Tree::ShuffleBag<int> > bag;

    typedef Tree::ShuffleBag<int>::List Ints;
    Ints bagged;
    Ints rest;
    int latest;

    sf::String shuffle_str;

    void ShuffleNext();

    sf::Sprite dude;
    sf::Sprite girl;

    sf::Sprite background;
};

