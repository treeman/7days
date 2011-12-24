#pragma once

#include <exception>
#include <stdexcept>
#include <string>

// Shortcut for making a new exception with a different name
#define MAKEEXCEPTION(name) \
class name : public my_exception { \
public: \
    name( std::string err ) : my_exception( err ) { } \
};

namespace Tree
{
    class my_exception : public std::exception {
    public:
        my_exception( const std::string err ) : s( err ) { }
        virtual ~my_exception() throw() { }
        virtual const char *what() const throw() {
            return s.c_str();
        }
    protected:
        const std::string s;
    };

    // A bunch of exceptions for different things

    // When a resource doesn't exist
    MAKEEXCEPTION(resource_not_found)

    // When a setting can't be found
    MAKEEXCEPTION(setting_not_found)

    // Something gone wrong with our lua loading
    MAKEEXCEPTION(lua_error)

    // A logical fault (similar to assert?)
    MAKEEXCEPTION(logical_fault)

    // Old version
    MAKEEXCEPTION(old_version)
}

