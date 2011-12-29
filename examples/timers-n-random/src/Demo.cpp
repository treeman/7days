#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include "Demo.hpp"

Demo::Demo()
{
    str = BUTLER->CreateString( "fnt/consola.ttf", 10 );
    str.SetColor( Tree::Color::white );

    st.SetSpeed( 2.0 );
    cd.SetLimit( 10 );

    Reset();

    for( int i = 0; i < MAGIC_NUM( "num_shuffle" ); ++i ) {
        shuffle_bag.Add( i );
    }

    weight_bag.Add( 0.6, "Strawberry" );
    weight_bag.Add( 0.2, "Apple" );
    weight_bag.Add( 0.2, "Orange" );

    Next();
}

bool Demo::HandleEvent( sf::Event &e )
{
    if( e.Type == sf::Event::KeyPressed ) {
        switch( e.Key.Code ) {
            case sf::Key::Return:
                Reset();
                break;
            case sf::Key::Space:
                t.Toggle();
                st.Toggle();
                cd.Toggle();
                break;
            case sf::Key::S:
                Next();
                break;
            case sf::Key::G:
                t.SetTime( 10 );
                st.SetTime( 10 );
                cd.SetTime( 10 );
                break;
            case sf::Key::Num1:
                st.SetSpeed( 0.5 );
                cd.SetSpeed( 0.5 );
                break;
            case sf::Key::Num2:
                st.SetSpeed( 1.0 );
                cd.SetSpeed( 1.0 );
                break;
            case sf::Key::Num3:
                st.SetSpeed( 2.0 );
                cd.SetSpeed( 2.0 );
                break;
            case sf::Key::F10:
                Tree::exit();
                break;
            default:
                break;
        }
    }

    return true;
}

void Demo::Update( float dt )
{
}

void Demo::Draw()
{
    Tree::clear_window( Tree::Color::black );

    // Draw timers
    str.SetText( boost::lexical_cast<std::string>( t.GetTime() ) );
    str.SetPosition( 100, 5 );
    Tree::draw( str );

    str.SetText( boost::lexical_cast<std::string>( st.GetTime() ) );
    str.SetPosition( 100, 15 );
    Tree::draw( str );

    str.SetText( boost::lexical_cast<std::string>( cd.GetTime() ) );
    str.SetPosition( 200, 5 );
    Tree::draw( str );

    if( cd.IsDone() ) {
        str.SetText( "done" );
    }
    else {
        str.SetText( "not done" );
    }
    str.SetPosition( 200, 15 );
    Tree::draw( str );

    // Draw shuffle bag's contents
    int n = 1;
    const float h = 10;
    for( Ints::iterator it = bagged.begin(); it != bagged.end(); ++it, ++n )
    {
        str.SetPosition( 10, 30 + h * n );
        str.SetText( boost::lexical_cast<std::string>( *it ) );
        Tree::draw( str );
    }

    n = 1;
    for( Ints::iterator it = rest.begin(); it != rest.end(); ++it, ++n )
    {
        str.SetPosition( 30, 30 + h * n );
        str.SetText( boost::lexical_cast<std::string>( *it ) );
        Tree::draw( str );
    }

    // Draw weight bag's selections
    typedef std::vector<std::string> Vals;
    typedef std::vector<float> Weights;

    Vals vals = weight_bag.GetVals();
    Weights weights = weight_bag.GetWeights();

    std::stringstream ss;
    ss.precision( 2 );

    n = 1;
    for( Weights::iterator it = weights.begin(); it < weights.end(); ++it, ++n ) {
        str.SetPosition( 60, 30 + h * n );
        ss.str("");
        ss << *it;
        str.SetText( ss.str() );
        Tree::draw( str );
    }

    n = 1;
    for( Vals::iterator it = vals.begin(); it < vals.end(); ++it, ++n ) {
        str.SetPosition( 85, 30 + h * n );
        str.SetText( boost::lexical_cast<std::string>( *it ) );
        Tree::draw( str );
    }

    str.SetPosition( 170, 40 );
    ss.str("");
    ss << "0.2: " << apples << " " << (float)apples / (float)total_weight
        << " Apples";
    str.SetText( ss.str() );
    Tree::draw( str );

    str.SetPosition( 170, 50 );
    ss.str("");
    ss << "0.2: " << oranges << " " << (float)oranges / (float)total_weight
        << " Oranges";
    str.SetText( ss.str() );
    Tree::draw( str );

    str.SetPosition( 170, 60 );
    ss.str("");
    ss << "0.6: " << strawberries << " " <<
        (float)strawberries / (float)total_weight << " Strawberries";
    str.SetText( ss.str() );
    Tree::draw( str );

    str.SetPosition( 170, 70 );
    str.SetText( "last: " + curr_weight );
    Tree::draw( str );
}

void Demo::Next()
{
    latest = shuffle_bag.Get();
    bagged = shuffle_bag.GetBag();
    rest = shuffle_bag.GetRest();

    curr_weight = weight_bag.Get();
    if( curr_weight == "Apple" ) ++apples;
    else if( curr_weight == "Orange" ) ++oranges;
    else if( curr_weight == "Strawberry" ) ++strawberries;

    ++total_weight;
}

void Demo::Reset()
{
    t.Restart();
    st.Restart();
    cd.Restart();
    total_weight = apples = oranges = strawberries = 0;
}

