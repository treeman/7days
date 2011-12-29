#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <stdarg.h>

#include "Singleton.hpp"

// Comment if we don't want to override BOOST_ASSERT
#define BOOST_ENABLE_ASSERT_HANDLER

#include <boost/assert.hpp>

/*
 * Our simple logging facility.
 * Logs to stdout and to a log file. Ability to log with c or c++ styles:
 *
 * L_ << "write me" << 2 << std::endl
 *   or
 * L_( "write me %d\n", 2 );
 *
 * Remember to init the log if you want to use a logfile.
 * Uses a macro L_ instead of something like *Tree::Log::Instance()( "write me...
 * I think it's better at least!
 */

#define L_ (*Tree::Log::Instance())

namespace Tree {

    class Log : public Tree::Singleton<Log> {
    public:
        Log();
        ~Log();

        void Init( std::string logfile );

        // stream style logging
        template<typename T>
        Log &operator << ( T var )
        {
            Write( var );
            return *this;
        }

        // printf style logging
        void operator() ( const char *msg, ... );
        void operator() ( std::string str );
    private:
        std::ofstream file;

        template<typename T>
        void Write( T var )
        {
            if( file.is_open() ) {
                file << var << std::flush;
            }
            std::cout << var << std::flush;
        }
    };
}

