#ifndef MISC_HPP_INCLUDED
#define MISC_HPP_INCLUDED

#include "Tree/Math.hpp"

namespace Tree {

	template<class Iterator>
	Iterator Random( Iterator first, Iterator last )
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
		
		int r = math::irandom( 0, n - 1 );
		for( int i = 0; i < n; ++i, ++first ) { 
			if( i == r ) {
				return first;
			}
		}
		return first;
	}
}

#endif
