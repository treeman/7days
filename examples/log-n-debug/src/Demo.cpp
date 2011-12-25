#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include "Demo.hpp"

Demo::Demo() : count(0)
{
    L_( "Demo started.\n" );

    str = BUTLER->CreateString( "fnt/consola.ttf", 10 );
    str.SetColor( Tree::Color::white );

    Tree::SetLogKey( sf::Key::M );
}

bool Demo::HandleEvent( sf::Event &e )
{
    if( e.Type == sf::Event::KeyPressed ) {
        switch( e.Key.Code ) {
            case sf::Key::Return:
                ++count;
                DP_( "lazy", "count = %d", count );
                break;
            case sf::Key::Space:
                Tree::DebugRemove( "lazy" );
                break;
            case sf::Key::Q:
                // Programming with assertions is a great way
                // not to program by coincidence
                BOOST_ASSERT( !"DIE DIE DIE" );
            case sf::Key::L:
                L_ << "Now we log. Count is: " << count << '\n';
            default:
                break;
        }
    }

    return true;
}

void Demo::Update( float dt )
{
    D_( "Debug!" );
    D_( "window = %dx%d", WINDOW_WIDTH, WINDOW_HEIGHT );
    D_( "magic str = %s num = %f", MAGIC_STRING( "shout" ).c_str(),
        MAGIC_NUM( "num" ) );

    if( Tree::ShallLog() ) {
        L_( "Lazy logging. This way we don't have to spam the log file!\n" );
    }
}

void Demo::Draw()
{
    Tree::ClearWindow( Tree::Color::black );
}

