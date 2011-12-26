#pragma once

#include <vector>

#include "Math.hpp"

namespace Tree
{
    template<typename T>
    class WeightBag {
    public:
        WeightBag() { }
        ~WeightBag() { }

        WeightBag &Add( float weight, T val );
        T Get();

        void Clear() { vals.clear(); weights.clear(); }
        bool IsEmpty() { return weights.empty(); }

        typedef std::vector<T> Vals;
        typedef std::vector<float> Weights;

        Vals GetVals() { return vals; }
        Weights GetWeights() { return weights; }
    private:
        Vals vals;
        Weights weights;
        float sum;
    };

    /** Template implementations **/

    template<typename T>
    WeightBag<T> &WeightBag<T>::Add( float weight, T val )
    {
        sum += weight;
        weights.push_back( sum );
        vals.push_back( val );

        return *this;
    }

    template<typename T>
    T WeightBag<T>::Get()
    {
        if( weights.empty() ) {
            throw( std::out_of_range( "Weightbag is empty" ) );
        }

        float rand = frandom( 0, sum );
        for( size_t i = 0; i < weights.size(); ++i ) {
            if( rand < weights[i] ) {
                return vals[i];
            }
        }

        // Should never come here
        // Only if rand = sum (which shouldn't happen if we randomize 0 < x < sum)
        return vals.back();
    }
}

