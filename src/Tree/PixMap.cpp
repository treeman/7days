#include "Util.hpp"
#include "Butler.hpp"
#include "Tweaks.hpp"

#include "PixMap.hpp"

PixMap::PixMap()
{
    mask = BUTLER->CreateSprite( TWEAKS->GetString( "pix_mask" ) );
    mask.SetBlendMode( sf::Blend::Multiply );

    pix_width = mask.GetSubRect().GetWidth();

    width = Tree::GetWindowWidth() / pix_width;
    height = Tree::GetWindowHeight() / pix_width;

    for( size_t x = 0; x < width; ++x ) {
        PixRow row;
        for( size_t y = 0; y < height; ++y ) {
            points_to_update.insert( Vec2i( x, y ) );

            row.insert( row.end(), 0x00000000 );
        }
        pixels.insert( pixels.end(), row );
    }
    next = pixels;
}

void PixMap::SetPix( Vec2i point, Tree::Color col )
{
    if( point.x >= 0 && point.x < (int)width &&
        point.y >= 0 && point.y < (int)height )
    {
        if( next[point.x][point.y] != col ) {
            next[point.x][point.y] = col;
            points_to_update.insert( point );
        }
    }
}
void PixMap::SetPix( int x, int y, Tree::Color col )
{
    SetPix( Vec2i( x, y ), col );
}

Tree::Color PixMap::GetPix( Vec2i point )
{
    return GetPix( point.x, point.y );
}
Tree::Color PixMap::GetPix( int x, int y )
{
    if( x >= 0 && x < (int)next.size() &&
        y >= 0 && y < (int)next[x].size() )
    {
        return next[x][y];
    }

    std::stringstream s;
    s << "Out of pixmap bounds: " << x << "," << y;
    throw Tree::logical_fault( s.str() );
}

int PixMap::Width() const
{
    return width;
}
int PixMap::Height() const
{
    return height;
}

void PixMap::Draw( sf::Sprite spr )
{
    const size_t w = spr.GetSubRect().GetWidth();
    const size_t h = spr.GetSubRect().GetHeight();

    for( size_t x = 0; x < w; ++x ) {
        for( size_t y = 0; y < h; ++y  ) {
            sf::Color col = spr.GetPixel( x, y );
            if( col.a != 0 ) {
                const Vec2i pos = spr.TransformToGlobal( Vec2i( x, y ) );
                SetPix( pos, col );
            }
        }
    }
}
void PixMap::Draw( PixSpr *const spr )
{
    PixSpr::Sprites sprs = spr->GetSprites();
    for( PixSpr::Sprites::iterator it = sprs.begin(); it != sprs.end(); ++it ) {
        Draw( *it );
    }
}

void PixMap::Draw()
{
    if( points_to_update.empty() ) return;

    size_t n = 0;
    for( Points::iterator it = points_to_update.begin();
        it != points_to_update.end(); )
    {
        //if( n > 120 * 40 ) break;
        if( n > 120 * 60 ) break;

        const Vec2i p( it->x, it->y );

        const sf::Color curr_col = pixels[p.x][p.y];
        const sf::Color new_col = next[p.x][p.y];

        // No need to redraw if it's already the same color
        if( curr_col == new_col ) {
            ++it;
        }
        else {
            //L_ << "Drawing pixel " << p << '\n';
            pixels[p.x][p.y] = new_col;

            const int rx = p.x * pix_width;
            const int ry = p.y * pix_width;

            Tree::Draw( sf::Shape::Rectangle(
                rx, ry,
                rx + pix_width, ry + pix_width,
                new_col
            ));
            mask.SetPosition( rx, ry );
            Tree::Draw( mask );

            Points::iterator it2 = it++;
            points_to_update.erase( it2 );
            ++n;
        }
    }
}

void PixMap::Redraw()
{
    for( size_t x = 0; x < width; ++x ) {
        for( size_t y = 0; y < height; ++y ) {
            // Reset current pixel to clear value
            // Force it to update when we get around to the drawing function
            pixels[x][y] = 0x00000000;
            points_to_update.insert( Vec2i( x, y ) );
        }
    }
}

