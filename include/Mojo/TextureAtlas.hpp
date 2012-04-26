#ifndef MOJO_TEXTURE_ATLAS_HPP
#define MOJO_TEXTURE_ATLAS_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Graphics.hpp>

namespace Mojo
{
    class MOJO_CLASS_EXPORT(TextureAtlas) : public Mojo::NonCopyable
    {
        public:
            TextureAtlas( const uint32_t width, const uint32_t height, const uint32_t bpp );
            ~TextureAtlas();

            Mojo::Texture Compile( const bool mipmap = true ) const;

        public:
            const uint32_t _width, _height, _bpp;
            uint8_t* _pixels;
    };
}

#endif /* MOJO_TEXTURE_ATLAS_HPP */