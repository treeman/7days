#include "Tree.hpp"
#include "Demo.hpp"

int main()
{
    L_.Init( "log.txt" );

    try {
        //create the game
        Tree::Game::Instance()->Init(
              800             //width
            , 600             //height
            , true            //windowed
            , "7days demo"    //window title
            , "settings.ini"  //settings file
            , true            //lazy drawing
        );

        //push your gamestates here
        {
            boost::shared_ptr<Tree::GameState> state( new Demo() );
            Tree::Game::Instance()->Push( state );
            state.reset( new Tree::Logo() );
            Tree::Game::Instance()->Push( state );
        }

        //start the main game loop
        Tree::Game::Instance()->Start();
    }
    catch( std::exception &e )
    {
        L_ << "Fatal exception: " << e.what() << '\n';
    }
    catch( ... )
    {
        L_ << "Not even Duke could handle this exception!\n";
    }

    //Destroy the singletons
    Tree::Game::Instance()->Destroy();
    L_.Destroy();

    return EXIT_SUCCESS;
}
