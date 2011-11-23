#pragma once

#include <boost/shared_ptr.hpp>

#include "Log.hpp"
#include "InputHandler.hpp"
#include "Util.hpp"

namespace Tree
{
    class LogHelper;

    class LogHelper : public InputHandler {
    public:
        LogHelper();

        bool ShallLog() const;

        void SetLogKey( int key );
        bool HandleEvent( sf::Event &e );

        void EndofLoop();
    private:
        bool shall_log;
        int one_iteration_key;
    };
}

