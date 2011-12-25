#include "Tree.hpp"
#include "Demo.hpp"

int main()
{
    L_.Init( "log.txt" );

    TWEAKS->Load( "magic_numbers.lua" );

    try {
        // Create the game
        GAME->Init(
              800             // width
            , 600             // height
            , true            // windowed
            , "Hello World!"  // window title
            , "settings.ini"  // settings file
            , true            // lazy drawing
        );

        // Push your gamestates here
        {
            boost::shared_ptr<Tree::GameState> state( new Demo() );
            GAME->Push( state );
        }

        // Start the main game loop
        GAME->Start();
    }
    catch( std::exception &e )
    {
        L_ << "Fatal exception: " << e.what() << '\n';
    }
    catch( ... )
    {
        L_ << "Not even Duke could handle this exception!\n";
    }

    // Destroy the singletons
    GAME->Destroy();
    L_.Destroy();

    return EXIT_SUCCESS;
}

