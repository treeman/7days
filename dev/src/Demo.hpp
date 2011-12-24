#pragma once

#include "Tree.hpp"

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

    Tree::CountDown cd;

    sf::String str;

    //testing the shufflebag
    boost::shared_ptr<Tree::ShuffleBag<int> > bag;

    typedef Tree::ShuffleBag<int>::List Ints;
    Ints bagged;
    Ints rest;
    int latest;

    void ShuffleNext();
    void SetTime( float speed );
    void SetSpeed( float speed );
    void Reset();
    void Toggle();

    sf::Sprite dude;
    sf::Sprite girl;

    sf::Sprite background;

    int count;

    Vec2i point;
};

