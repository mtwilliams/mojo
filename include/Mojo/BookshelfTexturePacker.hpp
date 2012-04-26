#ifndef MOJO_BOOKSHELF_TEXTURE_PACKER_HPP
#define MOJO_BOOKSHELF_TEXTURE_PACKER_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Math.hpp>
#include <Mojo/TextureAtlas.hpp>

namespace Mojo
{
    class MOJO_CLASS_EXPORT(BookshelfTexturePacker) : public Mojo::NonCopyable
    {
        public:
            BookshelfTexturePacker( Mojo::TextureAtlas* atlas );
            ~BookshelfTexturePacker();

            bool Pack( const uint32_t width, const uint32_t height, const uint32_t padding, const uint8_t* pixels, Mojo::Recti& packed_rect );

        private:
            Mojo::TextureAtlas* _atlas;
            uint32_t _x, _y, _shelf_height;
    };
}

#endif /* MOJO_TEXTURE_PACKER_BOOKSHELF_HPP */