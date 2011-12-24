#ifndef SHUFFLEBAG_HPP_INCLUDED
#define SHUFFLEBAG_HPP_INCLUDED

#include <vector>

#include "Exceptions.hpp"
#include "Math.hpp"

namespace Tree
{
    template<typename T>
    class ShuffleBag {
    public:
        ShuffleBag() { }
        ~ShuffleBag() { }

        // Add item to bag
        ShuffleBag &Add( T val )
        {
            bag.push_back( val );
            return *this;
        }

        // Take item from rest and place it in bag
        ShuffleBag &MakeAvailable( T val )
        {
            typename List::iterator it = std::find( rest.begin(), rest.end(), val );

            if( it != rest.end() ) {
                rest.erase( it );
                bag.push_back( val );
            }

            return *this;
        }

        // Return an item, remove from bag and place in rest
        // If bag is empty put back everything from rest in bag
        T Get()
        {
            if( IsEmpty() ) {
                throw( std::out_of_range( "Shufflebag is empty" ) );
            }

            if( bag.empty() ) {
                bag.swap( rest );
            }

            int i = Tree::irandom( 0, bag.size() - 1 );

            T item = bag.at(i);
            rest.push_back( item );
            bag.erase( bag.begin() + i );

            return item;
        }

        // Clear bag and rest
        void Clear()
        {
            bag.clear();
            rest.clear();
        }

        bool IsEmpty()
        {
            return bag.empty() && rest.empty();
        }

        typedef std::vector<T> List;

        List GetBag() { return bag; }
        List GetRest() { return rest; }
    private:
        List bag;
        List rest;
    };

}

#endif

