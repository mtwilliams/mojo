#include <Mojo/TextureAtlas.hpp>
#include <Mojo/Services.hpp>

namespace Mojo
{
    TextureAtlas::TextureAtlas( const uint32_t width, const uint32_t height, const uint32_t bpp )
        : _width(width)
        , _height(height)
        , _bpp(bpp)
        , _pixels( new uint8_t[width * height * bpp / 8] )
    {
        memset((void*)_pixels, 0, width * height * bpp / 8);
    }

    TextureAtlas::~TextureAtlas()
    {
        delete[] _pixels;
    }

    Mojo::Texture TextureAtlas::Compile( const bool mipmap ) const
    {
        Mojo::Graphics::TextureFormat tex_format;
        switch( _bpp ) {
            case 24: tex_format = Mojo::Graphics::TF_RGB8; break;
            case 32: tex_format = Mojo::Graphics::TF_RGBA8; break;
        }

        return MOJO_GET_SERVICE(Graphics)->CreateTexture2D(_width, _height, tex_format, (const void*)_pixels, mipmap);
    }
}