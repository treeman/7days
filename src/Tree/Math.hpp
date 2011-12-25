#ifndef MATH_HPP_INCLUDED
#define MATH_HPP_INCLUDED

#include <cmath>
#include <cstdlib>
#include <cfloat>

#include "Vec2D.hpp"

namespace Tree
{
    // Simple yet efficient
    static const float PI = 3.14159265358979323846f;
    static const float PI_2 = 1.57079632679489661923f;
    static const float PI_4 = 0.785398163397448309616f;
    static const float PI2 = 6.28318530717958647692f;
    static const float PI_SQR = 9.8696044010893586188344f;
    static const float INVPI = 0.318309886183790671538f;
    static const float INV2PI = 0.636619772367581343076f;

    template<class T>
    T interpolate( float dt, const T &x0, const T &x1 );

    template<typename T>
    inline const T clip( const T &x, const T &min, const T &max );

    // Clip length to min <= x <= max
    template<typename T>
    inline void clip( Vec2D<T> &v, const T &min, const T &max );

    float rad2deg( float rad );
    float deg2rad( float deg );

    // Transform a range [0-1] to [0-255]
    float enbyten( float zero_to_one );

    // 0 < x < 1
    extern const float frandom();
    // min < x < max
    extern const float frandom( float min, float max );

    // min <= x <= max
    extern const int irandom( int min, int max );

    /*      *
     *    * X *
     *      *       */
    extern std::vector<Vec2i> GenerateNeighbours( const Vec2i &v );

    /*    *   *
     *      X
     *    *   *     */
    extern std::vector<Vec2i> GenerateCorners( const Vec2i &v );

    /*    * * *
     *    * X *
     *    * * *     */
    extern std::vector<Vec2i> GenerateSurroundings( const Vec2i &v );

    /** emplate implementations **/

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
}

#endif

