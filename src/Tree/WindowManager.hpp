#pragma once

#include <boost/shared_ptr.hpp>
#include <string>
#include <SFML/Graphics.hpp>

#include "Dator.hpp"

// Maybe not necessary? Managers aren't particulary good...
namespace Tree
{
    class WindowManager {
    public:
        WindowManager();
        ~WindowManager();

        boost::shared_ptr<sf::RenderWindow> GetWindow() const { return window; }

        int Width();
        int Height();

        std::string SetWindowed( bool predicate );
        std::string SetScreenWidth( int val );
        std::string SetScreenHeight( int val );
        std::string SetScreenBPP( int val );
        std::string SetScreenTitle( std::string val );
        std::string SetFrameRate( int val );
    private:
        void UpdateWindow();
        boost::shared_ptr<sf::RenderWindow> window;

        boost::shared_ptr<Dator<int> > width;
        boost::shared_ptr<Dator<int> > height;
        boost::shared_ptr<Dator<int> > bpp;
        boost::shared_ptr<Dator<bool> > is_windowed;
        boost::shared_ptr<Dator<std::string> > title;
        boost::shared_ptr<Dator<int> > framerate;

        bool has_setup;
    };
}

