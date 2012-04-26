#include <Mojo/BookshelfTexturePacker.hpp>

namespace Mojo
{
    BookshelfTexturePacker::BookshelfTexturePacker( Mojo::TextureAtlas* atlas )
        : _atlas(atlas)
        , _x(0)
        , _y(0)
        , _shelf_height(0)
    {
    }

    BookshelfTexturePacker::~BookshelfTexturePacker()
    {
    }

    bool BookshelfTexturePacker::Pack( const uint32_t width, const uint32_t height, const uint32_t padding, const uint8_t* pixels, Mojo::Recti& packed_rect )
    {
        if( width == 0 || height == 0 || pixels == NULL ) return false;
        if( width + padding * 2 > _atlas->_width || height + padding * 2 > _atlas->_height ) return false;

        if( _x + width + padding * 2 > _atlas->_width ) {
            if( _y + _shelf_height + height + padding * 2 > _atlas->_height ) return false;
            _x = 0; _y += _shelf_height + padding;
            _shelf_height = height;
        } else {
            _shelf_height = _shelf_height < height ? height : _shelf_height;
        }

        const uint32_t bytes_per_pixel = (_atlas->_bpp / 8);
        const uint32_t src_pitch   = (width) * bytes_per_pixel;
        const uint32_t atlas_pitch = (_atlas->_width) * bytes_per_pixel;

        const uint8_t* src_ptr = pixels;
        uint8_t* dst_ptr = &_atlas->_pixels[((_x + padding) + (_y + padding) * _atlas->_width) * bytes_per_pixel];
        for( uint32_t y = 0; y < height; ++y ) {
            memcpy((void*)dst_ptr, (const void*)src_ptr, width * bytes_per_pixel);
            src_ptr += src_pitch;
            dst_ptr += atlas_pitch;
        }

        packed_rect.x      = _x + padding;
        packed_rect.y      = _y + padding;
        packed_rect.width  = width;
        packed_rect.height = height;

        _x += width + padding;
    }
}