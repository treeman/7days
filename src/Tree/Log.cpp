#include "Log.hpp"
#include <stdlib.h>

#ifdef BOOST_ENABLE_ASSERT_HANDLER

// Define boost assertion handler so we can log error message to file
void boost::assertion_failed(
    char const *expr, char const *function,
    char const *file, long line)
{
    L_("%s:%d: %s: Assertion '%s' failed.\n", file, line, function, expr);
    abort();
}

#endif

namespace Tree
{

Log::Log() { }
Log::~Log()
{
    if( file.is_open() ) {
        file.close();
    }
    std::cout << "Log file closed\n" << std::flush;
}

void Log::Init( std::string logfile )
{
    file.open( logfile.c_str() );
    std::cout << "Log file opened\n" << std::flush;
}

// printf style logging
void Log::operator() ( const char *msg, ... )
{
    va_list args;
    va_start( args, msg );
    char buf[1024];
    vsprintf( buf, msg, args );

    std::string str = buf;

    Write( str );
}
void Log::operator() ( std::string str )
{
    Write( str );
}

} // Namespace

