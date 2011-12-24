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

    str = BUTLER->CreateString( "fnt/consola.ttf", 10 );
    str.SetColor( Tree::Color( 0xFFFFFFFF ) );

    // Init shufflebag
    bag.reset( new Tree::ShuffleBag<int>() );

    //for( int i = 0; i < TWEAKS->GetNum( "boxes" ); ++i ) {
    for( int i = 0; i < MAGIC_NUM( "boxes" ); ++i ) {
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

    point( 400, 300 );
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
            case sf::Key::F10:
                Tree::Exit();
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
    D_( MAGIC_STRING( "shout" ) );
}

void Demo::Draw()
{
    Tree::Draw( background );

    str.SetText( boost::lexical_cast<std::string>( t.GetTime() ) );
    str.SetPosition( 50, 5 );
    Tree::Draw( str );

    str.SetText( boost::lexical_cast<std::string>( st.GetTime() ) );
    str.SetPosition( 50, 15 );
    Tree::Draw( str );

    str.SetText( boost::lexical_cast<std::string>( cd.GetTime() ) );
    str.SetPosition( 200, 5 );
    Tree::Draw( str );

    if( cd.IsDone() ) {
        str.SetText( "done" );
    }
    else {
        str.SetText( "not done" );
    }
    str.SetPosition( 200, 15 );
    Tree::Draw( str );

    // Draw shuffle bag's contents
    int n = 1;
    const float h = 10;
    for( Ints::iterator it = bagged.begin(); it != bagged.end(); ++it, ++n )
    {
        str.SetPosition( 10, 30 + h * n );
        str.SetText( boost::lexical_cast<std::string>( *it ) );
        Tree::Draw( str );
    }

    n = 1;
    for( Ints::iterator it = rest.begin(); it != rest.end(); ++it, ++n )
    {
        str.SetPosition( 30, 30 + h * n );
        str.SetText( boost::lexical_cast<std::string>( *it ) );
        Tree::Draw( str );
    }

    Tree::Draw( dude );
    Tree::Draw( girl );

    Vec2i mpos = Tree::GetMousePos();
    Vec2i l1 = point - mpos;
    if( l1.Magnitude() > 50 ) l1.SetMagnitude( 50 );

    Tree::Draw( sf::Shape::Line( point, point - l1, 1.0, Tree::Color( 0xff557733)));

    Vec2i p2( point.x, point.y - 50 );
    Vec2i l2 = point - p2;
    if( l1.Magnitude() > 50 ) l1.SetMagnitude( 50 );

    Tree::Draw( sf::Shape::Line( point, point - l2, 1.0, Tree::Color( 0xff775533)));

    float rad = angle( l1, l2 );

    str.SetPosition( point.x + 20, point.y - 30 );
    str.SetText( boost::lexical_cast<std::string>( rad ) );
    Tree::Draw( str );

    float degree = Tree::rad2deg( rad );

    str.SetPosition( point.x + 20, point.y - 20 );
    str.SetText( boost::lexical_cast<std::string>( degree ) );
    Tree::Draw( str );
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

