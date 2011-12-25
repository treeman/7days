#ifndef MATH_HPP_INCLUDED
#define MATH_HPP_INCLUDED

#include <cmath>
#include <cstdlib>
#include <cfloat>

#include "Vec2D.hpp"

namespace Tree
{
    static const float PI = 3.14159265358979323846f;
    static const float PI_2 = 1.57079632679489661923f;
    static const float PI_4 = 0.785398163397448309616f;
    static const float PI2 = 6.28318530717958647692f;
    static const float PI_SQR = 9.8696044010893586188344f;
    static const float INVPI = 0.318309886183790671538f;
    static const float INV2PI = 0.636619772367581343076f;

    template<class T> T interpolate( float dt, const T &x0, const T &x1 )
    {
        return x0 + ( (x1 - x0) * dt );
    }

    template<typename T>
    inline const T clip( const T &x, const T &min, const T &max ) {
        if( x < min ) return min;
        if( x > max ) return max;
        return x;
    }

    template<typename T>
    inline void clip( Vec2D<T> &v, const T &min, const T &max ) {
        const T l = v.Magnitude();
        if( l < min ) v.SetMagnitude( min );
        if( l > max ) v.SetMagnitude( max );
    }

    inline float rad2deg( float rad ) {
        return 180.0 / PI * rad;
    }

    inline float deg2rad( float deg ) {
        return deg / 180.0 * PI;
    }

    //transform a range [0-1] to [0-255]
    inline float enbyten( float zero_to_one )
    {
        if( zero_to_one == 0 ) return 0;
        else return zero_to_one / 1.0f * 255;
    }

    // 0 < x < 1
    inline const float frandom() {
        return (float)rand() / (float)RAND_MAX;
    }
    inline const float frandom( float min, float max ) {
        return min + ( frandom() * ( max - min ) );
    }

    // min <= x <= max
    inline const int irandom( int min, int max ) {
        if( min == max ) return min;
        return min + (int)( frandom() * ( max - min ) + 1 );
    }

    /*
     *      *
     *    * X *
     *      *
     */
    inline std::vector<Vec2i> GenerateNeighbours( const Vec2i &v )
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
    inline std::vector<Vec2i> GenerateCorners( const Vec2i &v )
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
    inline std::vector<Vec2i> GenerateSurroundings( const Vec2i &v )
    {
        std::vector<Vec2i> l1 = GenerateNeighbours( v );
        std::vector<Vec2i> l2 = GenerateCorners( v );
        l1.insert( l1.end(), l2.begin(), l2.end() );
        return l1;
    }
}

#endif

