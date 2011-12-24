#ifndef VEC2D_HPP_INCLUDED
#define VEC2D_HPP_INCLUDED

#include <cmath>
#include <ostream>
#include <SFML/Graphics.hpp>
#include <boost/unordered_set.hpp>
#include <sstream>

template<typename T>
class Vec2D {
public:
    Vec2D( const T _x = 0, const T _y = 0 ) : x(_x), y(_y) { }

    Vec2D( const Vec2D &v ) { x = v.x; y = v.y; }
    // implicit conversion between differently typed vectors
    template<typename S>
    Vec2D( const Vec2D<S> &v ) { x = v.x; y = v.y; }

    // implicit conversion between sfml's point type
    template<typename S>
    Vec2D( const sf::Vector2<S> &v ) { x = v.x; y = v.y; }
    template<typename S>
    operator sf::Vector2<S> () { return sf::Vector2<S>( x, y ); }

    Vec2D operator + ( const Vec2D &v ) const { return Vec2D( x + v.x, y + v.y ); }
    Vec2D operator - ( const Vec2D &v ) const { return Vec2D( x - v.x, y - v.y ); }
    Vec2D operator - () const { return Vec2D( -x, -y ); }
    Vec2D operator * ( T t ) const { return Vec2D( t * x, t * y ); }
    Vec2D operator / ( T t ) const { return Vec2D( x / t, y / t ); }

    void operator += ( const Vec2D &v ) { x += v.x; y += v.y; }
    void operator -= ( const Vec2D &v ) { x -= v.x; y -= v.y; }
    void operator *= ( T t ) { x *= t; y *= t; }
    void operator /= ( T t ) { x /= t; y /= t; }

    void operator = ( const Vec2D &v ) { x = v.x; y = v.y; }

    bool operator == ( const Vec2D &v ) const { return x == v.x && y == v.y; }
    bool operator != ( const Vec2D &v ) const { return !(*this == v); }

    // If we want to use it en a set we need them to be comparable unique
    // Hard to find a good way to compare, for now compare magnitude
    bool operator < ( const Vec2D &v ) const {
        return MagnitudeSq() < v.MagnitudeSq();
    }

    void operator () ( const T _x, const T _y ) { x = _x; y = _y; }

    T Magnitude() const { return std::sqrt( x * x + y * y ); }
    T MagnitudeSq() const { return x * x + y * y; }

    void SetMagnitude( const T f ) {
        const T m = Magnitude();
        if( m == 0 ) return;
        x = f * x / m;
        y = f * y / m;
    }

    Vec2D Normalize() const {
        const T mag = Magnitude();
        if( mag == 0 ) return *this;
        else return (*this) / mag;
    }

    T x, y;

    //names for common vectors
    static const Vec2D zero;
    static const Vec2D right;
    static const Vec2D left;
    static const Vec2D up;
    static const Vec2D down;
};

// work with boost hash functions eg unordered_set
template<typename T>
std::size_t hash_value( const Vec2D<T> &v )
{
    boost::hash<std::string> hasher;
    std::stringstream s;
    s << v;
    return hasher( s.str() );
}

typedef Vec2D<float> Vec2f;
typedef Vec2D<int> Vec2i;

template<typename T>
inline T dot( const Vec2D<T> v1, const Vec2D<T> v2 ) {
    return  v1.x * v2.x + v1.y * v2.y;
}

template<typename T>
inline float angle( const Vec2D<T> v1, const Vec2D<T> v2 ) {
    return std::atan2( v1.x, v1.y ) - std::atan2( v2.x, v2.y );
}

template<typename T>
inline Vec2D<T> operator * ( const T f, const Vec2D<T> v ) {
    return f * v;
}

template<typename T>
inline std::ostream &operator << ( std::ostream &o, const Vec2D<T> &v ) {
    return o << v.x << "," << v.y;
}

template<typename T>
inline std::istream &operator >> ( std::istream &i, Vec2D<T> &v ) {
    i >> v.x >> v.y;
    return i;
}

template<typename T>
const Vec2D<T> Vec2D<T>::zero( 0, 0 );
template<typename T>
const Vec2D<T> Vec2D<T>::left( -1, 0 );
template<typename T>
const Vec2D<T> Vec2D<T>::right( 1, 0 );
template<typename T>
const Vec2D<T> Vec2D<T>::up( 0, -1 );
template<typename T>
const Vec2D<T> Vec2D<T>::down( 0, 1 );

#endif

