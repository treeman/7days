#pragma once

#include "InputHandler.hpp"

namespace Tree
{
    class Game;

    class GameState : public InputHandler {
    public:
        virtual ~GameState() { }

        // Called before we run it
        // May happen more than once if we don't destroy it between switcing
        virtual void Loaded() { }

        // Same but before we unload it
        virtual void Unloaded() { }

        // Not necessary to overload this
        virtual bool HandleEvent( sf::Event &e ) { return true; }

        virtual void Update( float dt ) { }
        virtual void Draw() = 0;
    };
}

