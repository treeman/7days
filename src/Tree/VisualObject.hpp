#pragma once

#include "Graphics.hpp"
#include "Vec2D.hpp"
#include "DrawnLazy.hpp"

namespace Tree
{
    class VisualObject : public Tree::DrawnLazy {
    public:
        VisualObject();
        VisualObject( Vec2i pos );
        virtual ~VisualObject();

        void SetPos( Vec2i pos );
        void SetPos( int x, int y );
        Vec2i GetPos();

        void Move( int dx, int dy );
    protected:
        virtual void NewPos( Vec2i pos ) { }

        Vec2i pos;
    };
}

