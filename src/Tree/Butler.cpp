#include "Butler.hpp"

using Tree::Butler;

Butler::Butler()
{

}
Butler::~Butler()
{

}

void Butler::LoadSprites( std::string lua_file )
{
    spr_loader.Load( lua_file );
}

Tree::FntPtr Butler::GetFont( std::string path,
    unsigned int size ) throw( Tree::resource_load_error )
{
    typedef std::pair<FontMap::iterator, FontMap::iterator> ItPair;

    //find all fonts with the same font file
    ItPair ret = font_map.equal_range( path );
    if( ret.first != ret.second ) {

        //search for the same font size
        //it's important because otherwise they'll get blurry and ugly
        for( FontMap::iterator it = ret.first; it != ret.second; ++it ) {
            if( it->second->GetCharacterSize() == size ) {
                return it->second;
            }
        }
    }
    FntPtr fnt( new sf::Font() );

    if( !fnt->LoadFromFile( path.c_str(), size ) ) {
        throw( Tree::resource_load_error( "Unable to load font: '" + path + "'" ) );
    }

    font_map.insert( std::make_pair( path, fnt ) );
    return fnt;
}

Tree::ImgPtr Butler::GetImage( std::string path, bool shall_smooth )
    throw( Tree::resource_load_error )
{
    ImageMap::iterator it = image_map.find( path );
    if( it != image_map.end() ) {
        return it->second;
    }
    else {
        ImgPtr img( new sf::Image() );

        if( !img->LoadFromFile( path.c_str() ) ) {
            throw( Tree::resource_load_error(
                "Unable to load image: '" + path + "'" ) );
        }
        img->SetSmooth( shall_smooth );

        image_map.insert( std::make_pair( path, img ) );
        return img;
    }
}

Tree::SndPtr Butler::GetSoundBuffer( std::string path )
    throw( Tree::resource_load_error )
{
    SoundMap::iterator it = sound_map.find( path );
    if( it != sound_map.end() ) {
        return it->second;
    }
    else {
        SndPtr snd( new sf::SoundBuffer() );

        if( !snd->LoadFromFile( path.c_str() ) ) {
            throw( Tree::resource_load_error(
                "Unable to load sound: '" + path + "'" ) );
        }

        sound_map.insert( std::make_pair( path, snd ) );
        return snd;
    }
}

sf::Sprite Butler::CreateSprite(
    std::string img_path, int index, int width, int height )
    throw( Tree::resource_load_error )
{
    return CreateSprite( *GetImage( img_path ), index, width, height );
}

sf::Sprite Butler::CreateSprite(
    const sf::Image &image, int index, int width, int height )
    throw( Tree::resource_load_error )
{
    const int num_wide = image.GetWidth() / width;
    const int num_high = image.GetHeight() / height;

    const int tot_index = num_wide * num_high;

    if( index >= tot_index ) {
        std::stringstream ss;
        ss << "Index " << index << " out of bounds when indexing image\n";
        throw( Tree::resource_load_error( ss.str() ) );
    }

    const int x_index = index % num_wide;
    const int y_index = index / num_wide;

    const int x = x_index * width;
    const int y = y_index * height;

    sf::Sprite spr;
    spr.SetImage( image );
    spr.SetSubRect( sf::IntRect( x, y, x + width, y + height ) );
    return spr;
}

sf::Sprite Butler::CreateSprite( std::string name )
    throw( Tree::resource_load_error )
{
    if( spr_loader.HasCustomSprite( name ) ) {
        return spr_loader.Create( name );
    }
    else {
        try {
            sf::Sprite spr;
            spr.SetImage( *GetImage( name ) );
            return spr;
        }
        catch( Tree::resource_load_error & ) {
            throw( Tree::resource_load_error(
                "Unable to load sprite: '" + name + "'" ) );
        }
    }
}

sf::String Butler::CreateString( std::string fnt_path, int size )
    throw( Tree::resource_load_error )
{
    sf::String str;
    str.SetFont( *GetFont( fnt_path, size ) );
    str.SetSize( size );
    return str;
}

sf::Sound Butler::CreateSound( std::string path )
    throw( Tree::resource_load_error )
{
    sf::Sound snd;
    snd.SetBuffer( *GetSoundBuffer( path ) );
    return snd;
}

