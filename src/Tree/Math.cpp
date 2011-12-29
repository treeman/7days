#include "Math.hpp"

namespace Tree {

float rad2deg( float rad ) {
    return 180.0 / PI * rad;
}
float deg2rad( float deg ) {
    return deg / 180.0 * PI;
}

// Transform a range [0-1] to [0-255]
float enbyten( float zero_to_one )
{
    if( zero_to_one == 0 ) return 0;
    else return zero_to_one / 1.0f * 255;
}

// 0 < x < 1
const float frandom() {
    return (float)rand() / (float)RAND_MAX;
}
const float frandom( float min, float max ) {
    return min + ( frandom() * ( max - min ) );
}

// min <= x <= max
const int irandom( int min, int max ) {
    if( min == max ) return min;
    return min + (int)( frandom() * ( max - min ) + 1 );
}

/*
    *      *
    *    * X *
    *      *
    */
std::vector<Vec2i> generate_neighbours( const Vec2i &v )
{
    std::vector<Vec2i> l;
    l.push_back( Vec2i( v.x - 1, v.y ) );
    l.push_back( Vec2i( v.x + 1, v.y ) );
    l.push_back( Vec2i( v.x, v.y - 1 ) );
    l.push_back( Vec2i( v.x, v.y + 1 ) );
    return l;
}

/*
    *    *   *
    *      X
    *    *   *
    */
std::vector<Vec2i> generate_corners( const Vec2i &v )
{
    std::vector<Vec2i> l;
    l.push_back( Vec2i( v.x - 1, v.y - 1 ) );
    l.push_back( Vec2i( v.x - 1, v.y + 1 ) );
    l.push_back( Vec2i( v.x + 1, v.y - 1 ) );
    l.push_back( Vec2i( v.x + 1, v.y + 1 ) );
    return l;
}

/*
    *    * * *
    *    * X *
    *    * * *
    */
std::vector<Vec2i> generate_surroundings( const Vec2i &v )
{
    std::vector<Vec2i> l1 = generate_neighbours( v );
    std::vector<Vec2i> l2 = generate_corners( v );
    l1.insert( l1.end(), l2.begin(), l2.end() );
    return l1;
}

}

