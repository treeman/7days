#pragma once

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

#include "Util.hpp"

// Load a lua file with numbers or strings in it. Like a config or a tweak file.
namespace Tree
{
    class Tweaks {
    public:
        Tweaks();

        void Load( std::string path );

        double GetNum( std::string s );
        bool HasNum( std::string s );
        void SetNum( std::string s, double val );

        std::string GetString( std::string s );
        bool HasString( std::string s );
        void SetString( std::string s, std::string val );
    private:
        typedef std::map<std::string, double> DoubleMap;
        DoubleMap doubles;

        typedef std::map<std::string, std::string> StringMap;
        StringMap strings;
    };
}

