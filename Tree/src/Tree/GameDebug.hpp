#pragma once

#include <boost/shared_ptr.hpp>

#include "Tree/Graphics.hpp"
#include "Tree/InputHandler.hpp"
#include "Settings.hpp"
#include "Dator.hpp"

namespace Tree
{
    class GameDebug : public InputHandler {
    public:
        GameDebug();

        bool HandleEvent( sf::Event &e );

        void Update( float dt );
        void Draw();
    private:
        boost::shared_ptr<Dator<bool> > show_mouse_pos;
        boost::shared_ptr<Dator<bool> > show_fps;

        sf::String fps;
        sf::String mpos;
    };
}

