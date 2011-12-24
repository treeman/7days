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

        WeightBag &Add( float weight, T val )
        {
            sum += weight;
            weights.push_back( sum );
            vals.push_back( val );

            return *this;
        }

        T Get()
        {
            if( weights.empty() ) {
                throw( std::out_of_range( "Weightbag is empty" ) );
            }

            float rand = frandom( 0, sum );
            DP_( "rand", "%.4f", rand );
            for( size_t i = 0; i < weights.size(); ++i ) {
                if( rand < weights[i] ) {
                    return vals[i];
                }
            }

            // Should never come here
            // Only if rand = sum
            return vals.back();
        }

        typedef std::vector<T> Vals;
        typedef std::vector<float> Weights;

        Vals GetVals() { return vals; }
        Weights GetWeights() { return weights; }
    private:
        Vals vals;
        Weights weights;
        float sum;
    };
}

