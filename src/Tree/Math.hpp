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

    inline float rad2deg( float rad ) {
        return 180.0 / PI * rad;
    }

    inline float deg2rad( float deg ) {
        return deg / 180.0 * PI;
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

    template<class Iterator>
    Iterator random( Iterator first, Iterator last )
    {
        //will crash if first == last
        if( first == last ) {
            return first;
        }
        int n = 0;
        Iterator it = first;
        for( ; it != last; ++it ) {
            ++n;
        }
        if( n == 1 ) {
            return first;
        }

        int r = irandom( 0, n - 1 );
        for( int i = 0; i < n; ++i, ++first ) {
            if( i == r ) {
                return first;
            }
        }
        return first;
    }

    //transform a range [0-1] to [0-255]
    inline float enbyten( float zero_to_one )
    {
        if( zero_to_one == 0 ) return 0;
        else return zero_to_one / 1.0f * 255;
    }
}

#endif

