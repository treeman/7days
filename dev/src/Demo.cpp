#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include "Demo.hpp"

Demo::Demo() : count(0)
{
    st.SetSpeed( 2 );
    cd.SetLimit( 10 );

    t.Start();
    st.Start();
    cd.Start();

    time_str = BUTLER->CreateString( "fnt/consola.ttf", 10 );
    time_str.SetColor( Tree::Color( 0xFFFFFFFF ) );

    shuffle_str = BUTLER->CreateString( "fnt/consola.ttf", 10 );
    shuffle_str.SetColor( sf::Color( 255, 255, 255 ) );

    // Init shufflebag
    bag.reset( new Tree::ShuffleBag<int>() );

    for( int i = 0; i < TWEAKS->GetNum( "boxes" ); ++i ) {
        bag->Add( i );
    }
    ShuffleNext();

    // Need to load sprites file
    BUTLER->LoadSprites( "sprites.lua" );

    dude = BUTLER->CreateSprite( "dude" );
    dude.SetPosition( 230, 200 );

    girl = BUTLER->CreateSprite( "girl" );
    girl.SetPosition( 400, 150 );

    background = BUTLER->CreateSprite( "gfx/dude.png" );
    background.SetPosition( 0, 0 );

    L_( "hi: %d\n", 1337 );
}

bool Demo::HandleEvent( sf::Event &e )
{
    if( e.Type == sf::Event::KeyPressed ) {
        switch( e.Key.Code ) {
            case( sf::Key::Return ):
                Reset();
                break;
            case sf::Key::Space:
                Toggle();
                break;
            case sf::Key::G:
                SetTime( 10.0 );
                break;
            case sf::Key::Num1:
                SetSpeed( 0.5 );
                break;
            case sf::Key::Num2:
                SetSpeed( 1.0 );
                break;
            case sf::Key::Num3:
                SetSpeed( 2.0 );
                break;
            case sf::Key::S:
                ShuffleNext();
                break;
            case sf::Key::C:
                ++count;
                Tree::DebugPersist( "persist", "count %d", count );
                break;
            case sf::Key::R:
                Tree::DebugRemove( "persist" );
                break;
            default:
                break;
        }
    }
    return true;
}

void Demo::Update( float dt )
{
    Tree::Debug( "Debug!" );
    D_( "window = %dx%d", WINDOW_WIDTH, WINDOW_HEIGHT );
}

void Demo::Draw()
{
    Tree::Draw( background );

    time_str.SetText( boost::lexical_cast<std::string>( t.GetTime() ) );
    time_str.SetPosition( 50, 5 );
    Tree::Draw( time_str );

    time_str.SetText( boost::lexical_cast<std::string>( st.GetTime() ) );
    time_str.SetPosition( 50, 15 );
    Tree::Draw( time_str );

    time_str.SetText( boost::lexical_cast<std::string>( cd.GetTime() ) );
    time_str.SetPosition( 200, 5 );
    Tree::Draw( time_str );

    if( cd.IsDone() ) {
        time_str.SetText( "done" );
    }
    else {
        time_str.SetText( "not done" );
    }
    time_str.SetPosition( 200, 15 );
    Tree::Draw( time_str );

    // Draw shuffle bag's contents
    int n = 1;
    const float h = 10;
    for( Ints::iterator it = bagged.begin(); it != bagged.end(); ++it, ++n )
    {
        shuffle_str.SetPosition( 10, 30 + h * n );
        shuffle_str.SetText( boost::lexical_cast<std::string>( *it ) );
        Tree::Draw( shuffle_str );
    }

    n = 1;
    for( Ints::iterator it = rest.begin(); it != rest.end(); ++it, ++n )
    {
        shuffle_str.SetPosition( 30, 30 + h * n );
        shuffle_str.SetText( boost::lexical_cast<std::string>( *it ) );
        Tree::Draw( shuffle_str );
    }

    Tree::Draw( dude );
    Tree::Draw( girl );
}

void Demo::ShuffleNext()
{
    latest = bag->Get();
    bagged = bag->GetBag();
    rest = bag->GetRest();
}

void Demo::SetSpeed( float speed )
{
    st.SetSpeed( speed );
    cd.SetSpeed( speed );
}
void Demo::SetTime( float time )
{
    t.SetTime( time );
    st.SetTime( time );
    cd.SetTime( time );
}
void Demo::Reset()
{
    t.Restart();
    st.Restart();
    cd.Restart();
    count = 0;
}
void Demo::Toggle()
{
    t.Toggle();
    st.Toggle();
    cd.Toggle();
}

