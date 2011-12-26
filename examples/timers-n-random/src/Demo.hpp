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

    Tree::Timer t;
    Tree::Timer st;
    Tree::CountDown cd;

    Tree::ShuffleBag<int> shuffle_bag;
    typedef Tree::ShuffleBag<int>::List Ints;
    Ints bagged;
    Ints rest;
    int latest;

    Tree::WeightBag<std::string> weight_bag;
    int apples, oranges, strawberries;
    int total_weight;
    std::string curr_weight;

    void Next();
    void Reset();
};

