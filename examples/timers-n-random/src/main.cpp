#include "Tree.hpp"
#include "Demo.hpp"

int main()
{
    L_.Init( "log.txt" );

    try {
        // Load magic numbers
        TWEAKS->Load( "magic_numbers.lua" );

        // Load custom sprites
        BUTLER->LoadSprites( "sprites.lua" );

        // We need at least this version to be able to build
        Tree::request_version( 0.1 );

        // Create the game
        GAME->Init(
              800             // width
            , 600             // height
            , true            // windowed
            , "Timers&Random" // window title
            , "settings.ini"  // settings file
            , false           // lazy drawing
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

