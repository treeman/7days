#pragma once

#include <boost/shared_ptr.hpp>

#include "Graphics.hpp"
#include "InputHandler.hpp"
#include "Settings.hpp"
#include "Dator.hpp"
#include "DrawnLazy.hpp"

namespace Tree
{
    class GameDebug : public InputHandler, public DrawnLazy {
    public:
        GameDebug();

        bool HandleEvent( sf::Event &e );

        void Update( float dt );
    private:
        void Render();

        boost::shared_ptr<Dator<bool> > show_mouse_pos;
        boost::shared_ptr<Dator<bool> > show_fps;

        sf::String fps;
        sf::String mpos;
    };
}

