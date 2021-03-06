#include "DrawnLazy.hpp"
#include "Graphics.hpp"
#include "Log.hpp"

using Tree::DrawnLazy;

DrawnLazy::DrawnLazy() : need_to_redraw( true )
{ }
DrawnLazy::~DrawnLazy()
{ }

// one function to render it lazily
void DrawnLazy::Draw()
{
    if( WillRedraw() ) { ForceDraw(); }
}
void DrawnLazy::ForceDraw()
{
    Render();
    need_to_redraw = false;
}
// flag for us to redraw when we call draw
void DrawnLazy::Redraw()
{
    need_to_redraw = true;
}
bool DrawnLazy::WillRedraw()
{
    return need_to_redraw || Tree::need_redraw() || !drawing_lazy();
}

