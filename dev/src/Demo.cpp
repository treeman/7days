#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include "Demo.hpp"

Demo::Demo() : count(0)
{
    st.SetSpeed( 2 );
    cd.SetLimit( 10 );

    Reset();

    str = BUTLER->CreateString( "fnt/consola.ttf", 10 );
    str.SetColor( Tree::Color( 0xFFFFFFFF ) );

    // Init shufflebag
    bag.reset( new Tree::ShuffleBag<int>() );

    for( int i = 0; i < MAGIC_NUM( "boxes" ); ++i ) {
        bag->Add( i );
    }

    L_( "hi: %d\n", 1337 );

    point( 400, 300 );

    weight_bag.Add( 0.6, "Strawberry" );
    weight_bag.Add( 0.2, "Apple" );
    weight_bag.Add( 0.2, "Orange" );

    ShuffleNext();

    Tree::set_log_key( sf::Key:: L );

    for( int i = 0; i < 8; ++i ) {
        // Create indexed sprite from file
        sprites.push_back( BUTLER->CreateSprite( "gfx/tiles.png", i, 32, 32 ) );
    }

    aspr = BUTLER->CreateSprite( "gfx/dod.png" );
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
                Tree::debug_persist( "persist", "count %d", count );
                break;
            case sf::Key::R:
                Tree::debug_remove( "persist" );
                break;
            case sf::Key::F10:
                Tree::exit();
                break;
            case sf::Key::Q:
                BOOST_ASSERT(!"DIE DIE DIE");
                break;
            /*case sf::Key::W:
                BOOST_ASSERT_MSG(1 == 0, "Slower death\n");
                break;*/
            default:
                break;
        }
    }
    return true;
}

void Demo::Update( float dt )
{
    Tree::debug( "Debug!" );
    D_( "window = %dx%d", WINDOW_WIDTH, WINDOW_HEIGHT );
    D_( MAGIC_STRING( "shout" ) );

    if( Tree::shall_log() ) {
        L_( "Log when needed\n" );
    }
}

void Demo::Draw()
{
    Tree::clear_window( Tree::Color::black );

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

    Vec2i mpos = Tree::get_mouse_pos();
    Vec2i l1 = point - mpos;
    Tree::clip( l1, 0, 50 );

    Tree::draw( sf::Shape::Line( point, point - l1, 1.0, Tree::Color( 0xff557733)));

    Vec2i p2( point.x, point.y - 50 );
    Vec2i l2 = point - p2;
    Tree::clip( l2, 0, 50 );

    Tree::draw( sf::Shape::Line( point, point - l2, 1.0, Tree::Color( 0xff775533)));

    float rad = angle( l1, l2 );

    str.SetPosition( point.x + 20, point.y - 30 );
    str.SetText( boost::lexical_cast<std::string>( rad ) );
    Tree::draw( str );

    float degree = Tree::rad2deg( rad );

    str.SetPosition( point.x + 20, point.y - 20 );
    str.SetText( boost::lexical_cast<std::string>( degree ) );
    Tree::draw( str );

    // Check neighbours
    str.SetPosition( 250, 350 );
    str.SetText( "neighbours" );
    Tree::draw( str );

    typedef std::vector<Vec2i> Points;
    Points ps = Tree::generate_neighbours( point );
    n = 1;
    for( Points::iterator it = ps.begin(); it < ps.end(); ++it, ++n ) {
        str.SetPosition( 250, 350 + h * n );
        str.SetText( boost::lexical_cast<std::string>( *it ) );
        Tree::draw( str );
    }

    str.SetPosition( 320, 350 );
    str.SetText( "corners" );
    Tree::draw( str );

    ps = Tree::generate_corners( point );
    n = 1;
    for( Points::iterator it = ps.begin(); it < ps.end(); ++it, ++n ) {
        str.SetPosition( 320, 350 + h * n );
        str.SetText( boost::lexical_cast<std::string>( *it ) );
        Tree::draw( str );
    }

    str.SetPosition( 400, 350 );
    str.SetText( "both" );
    Tree::draw( str );

    ps = Tree::generate_surroundings( point );
    n = 1;
    for( Points::iterator it = ps.begin(); it < ps.end(); ++it, ++n ) {
        str.SetPosition( 400, 350 + h * n );
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
        //str.SetText( boost::lexical_cast<std::string>( *it ) );
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

    // Draw shapes
    Tree::draw_line( 500, 200, 520, 220, Tree::Color::white );
    Tree::draw_line( 520, 220, 540, 180, Tree::Color::yellow, 2.0 );
    Tree::draw_line( Vec2i( 540, 180 ), Vec2i( 560, 200 ),
        Tree::Color::magenta, 2.0, Tree::Color::cyan, 1.0 );

    Tree::draw_rect( 600, 100, 640, 140, Tree::Color::blue );
    Tree::draw_rect( 600, 200, 640, 240, Tree::Color::green,
        Tree::Color::red, 1.0 );

    Tree::draw_circle( 700, 250, 40, Tree::Color::white );

    Tree::draw_triangle( 610, 300, 600, 320, 620, 320, Tree::Color::white );
    Tree::draw_triangle( 610, 360, 600, 340, 620, 340, Tree::Color::white,
        Tree::Color::red, 2.0 );

    // Draw statusbar
    float perc = st.GetTime() - (int)(st.GetTime() / 2.0) * 2.0;
    Tree::draw_bar( 700, 580, 790, 590, perc, Tree::Color( 0xff333333 ),
        Tree::Color( 0xffaaaaaa ), Tree::Color::white, 1.0 );

    // Draw indexed sprites
    for( size_t i = 0; i < sprites.size(); ++i ) {
        sf::Sprite &spr = sprites[i];
        spr.SetPosition( 40 + i * 32, 530 );
        Tree::draw( spr );
    }

    // Draw regular sprite
    aspr.SetPosition( 50, 200 );
    if( perc > 1.0 ) perc = 1.0;
    Tree::set_alpha( aspr, Tree::enbyten( perc ) );
    Tree::draw( aspr );
}

void Demo::ShuffleNext()
{
    latest = bag->Get();
    bagged = bag->GetBag();
    rest = bag->GetRest();

    curr_weight = weight_bag.Get();
    if( curr_weight == "Apple" ) ++apples;
    else if( curr_weight == "Orange" ) ++oranges;
    else if( curr_weight == "Strawberry" ) ++strawberries;

    ++total_weight;
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
    total_weight = apples = oranges = strawberries = 0;
}
void Demo::Toggle()
{
    t.Toggle();
    st.Toggle();
    cd.Toggle();
}

