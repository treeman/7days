#pragma once

#include <string>
#include <vector>
#include <map>

#include "Graphics.hpp"
#include "DrawnLazy.hpp"

namespace Tree
{
    class VisualDebug : public DrawnLazy {
    public:
        VisualDebug();

        void Add( std::string s );
        void SetPersistent( std::string id, std::string s );
        void RemovePersistent( std::string id );

        void ResetTempStrings();
    private:
        void Render();

        Strings temp;
        StringMap persistent;

        sf::String render_str;
        const int x_pos;
        const int y_pos;
        const int line_height;
    };
}

