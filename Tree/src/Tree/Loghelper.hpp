#pragma once

#include "Tree/Log.hpp"
#include "Tree/InputHandler.hpp"

namespace Tree
{
    class LogHelper;

    boost::shared_ptr<LogHelper> GetLogHelper();

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

