#include <Mojo/Font.hpp>
#include <Mojo/Debug.hpp>
#include <Mojo/Services.hpp>
#include <Mojo/TextureAtlas.hpp>
#include <Mojo/BookshelfTexturePacker.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

namespace Mojo
{
    static FT_Library& GetFreeTypeLibrary()
    {
        static FT_Library library;
        static bool initialized = false;
        if( !initialized ) {
            const FT_Error fterror = FT_Init_FreeType(&library);
            mojo_assertf(!fterror, "Mojo::GetFreeTypeLibrary()\n -> Failed to initialize FreeType.\n");
            initialized = true;
        }
        return library;
    }

    Font::Font()
        : _start_glyph(0)
        , _num_glyphs(0)
        , _glyphs(NULL)
        , _line_height(0.0f)
        , _font_atlas(Mojo::Texture::invalid)
    {
    }

    Font::~Font()
    {
        delete[] _glyphs;
    }

    Mojo::Rectf Font::Measure( const char* string )
    {
        // bug: the width measurement is slightly off

        char last_ch = '\0';
        float x_max = 0.0f, y_max = 0.0f;
        float x_offset = 0.0f, y_offset = 0.0f;
        while( const char ch = *string++ ) {
            last_ch = ch;
            x_max = x_max < x_offset ? x_offset : x_max; 

            switch( ch ) {
                case ' ':  x_offset += _glyphs[' ' - _start_glyph].x_advance; break;
                case '\t': x_offset += _glyphs[' ' - _start_glyph].x_advance * 4; break;
                case '\n': x_offset = 0.0f; y_offset += GetLineHeight() + 1.0f; break;
                case '\r': break;
                default: {
                    x_offset += _glyphs[ch - _start_glyph].x_advance + _glyphs[ch - _start_glyph].x_bearing;
                    const float my = y_offset + _base_line - _glyphs[ch - _start_glyph].y_bearing + _glyphs[ch - _start_glyph].height;
                    y_max = y_max < my ? my : y_max;
                } break;
            }
        }

        return Mojo::Rectf(0.0f, 0.0f, x_max, y_max);
    }

    bool Font::CreateFromFile( const char* path, const uint32_t font_size, const uint32_t start_char, const size_t num_chars )
    {
        if( path == NULL || font_size == 0 || num_chars == 0 || _num_glyphs > 0 ) return false;

        Mojo::Services::Filesystem* filesystem = MOJO_GET_SERVICE(Filesystem);
        Mojo::Filesystem::File* file = filesystem->Open(path, Mojo::Filesystem::FILE_READ);
        if( !file ) return false;

        size_t file_len = filesystem->Length(file);
        if( file_len == 0 ) {
            filesystem->Close(file);
            return false;
        }

        // todo: Use FT_Open_Face to read the file instead?

        uint8_t* buffer = new uint8_t[file_len]; {
            uint32_t num_bytes_read = 0;
            while( num_bytes_read < file_len ) {
                size_t read = filesystem->Read(file, file_len - num_bytes_read, (void*)&buffer[num_bytes_read]);
                mojo_assertf(read > 0, "Font::CreateFromFile\n -> Services/Filesystem error?\n");
                num_bytes_read += read;
            }
        }

        filesystem->Close(file);

        FT_Face ft_face;
        if( FT_New_Memory_Face(Mojo::GetFreeTypeLibrary(), (const FT_Byte*)buffer, file_len, 0, &ft_face) ) {
            delete[] buffer;
            return false;
        }

        FT_Set_Char_Size(ft_face, font_size * 64, font_size * 64, 96, 96);

        const float line_height = ft_face->size->metrics.height >> 6;

        // Load the glyphs
        Font::Glyph*    glyphs       = new Font::Glyph[num_chars];
        FT_Glyph*       ft_glyphs    = new FT_Glyph[num_chars];
        FT_BitmapGlyph* bm_glyphs    = (FT_BitmapGlyph*)ft_glyphs;

        uint32_t bm_max_width = 0, bm_max_height = 0;
        for( uint32_t i = 0; i < num_chars; ++i ) {
            FT_Load_Char(ft_face, start_char + i, FT_LOAD_DEFAULT);
            FT_Get_Glyph(ft_face->glyph, &ft_glyphs[i]);

            glyphs[i].x_advance = ft_face->glyph->advance.x >> 6;
            glyphs[i].y_advance = ft_face->glyph->advance.y >> 6;
            glyphs[i].x_bearing = (FT_HAS_VERTICAL(ft_face) ? ft_face->glyph->metrics.vertBearingX : ft_face->glyph->metrics.horiBearingX) >> 6;
            glyphs[i].y_bearing = (FT_HAS_VERTICAL(ft_face) ? ft_face->glyph->metrics.vertBearingY : ft_face->glyph->metrics.horiBearingY) >> 6;
            
            FT_Glyph_To_Bitmap(&ft_glyphs[i], FT_RENDER_MODE_NORMAL, 0, 1);

            const FT_Bitmap bitmap = bm_glyphs[i]->bitmap;
            glyphs[i].width  = bitmap.width;
            glyphs[i].height = bitmap.rows;

            bm_max_width  = bm_max_width < bitmap.width ? bitmap.width : bm_max_width;
            bm_max_height = bm_max_height < bitmap.rows ? bitmap.rows : bm_max_height;
        }

        // Determine the texture atlas size
        uint32_t atlas_width = 0, atlas_height = 0; {
            static const struct { uint32_t width, height, area; } atlas_sizes[] = {
                {  64,  64,  64 *  64 }, { 128, 128, 128 * 128 },
                { 256, 256, 256 * 256 }, { 512, 512, 512 * 512 }
            };

            uint32_t min_area = 0;
            for( uint32_t i = 0; i < num_chars; ++i ) min_area += uint32_t((glyphs[i].width + 1) * (glyphs[i].height + 1));

            for( uint32_t i = 0; i < 4; ++i ) {
                if( atlas_sizes[i].area < min_area ) continue;

                const uint32_t index = (i + 1) > 4 ? 4 : (i + 1);
                atlas_width  = atlas_sizes[index].width;
                atlas_height = atlas_sizes[index].height;
                break;
            }

            if( atlas_width == 0 || atlas_height == 0 ) {
                for( uint32_t i = 0; i < num_chars; ++i ) FT_Done_Glyph(ft_glyphs[i]);
                delete[] ft_glyphs;
                delete[] glyphs;

                FT_Done_Face(ft_face);
                delete[] buffer;

                return false;
            }
        }

        Mojo::TextureAtlas tex_atlas = Mojo::TextureAtlas(atlas_width, atlas_height, 32);
        Mojo::BookshelfTexturePacker tex_packer = Mojo::BookshelfTexturePacker(&tex_atlas);

        uint8_t* bm_buffer = new uint8_t[bm_max_width * bm_max_height * 4];
        for( uint32_t i = 0; i < num_chars; ++i ) {
            const FT_Bitmap bitmap = bm_glyphs[i]->bitmap;
            if( bitmap.width == 0 || bitmap.rows == 0 ) continue;

            memset((void*)bm_buffer, 255, bm_max_width * bm_max_height * 4);

            switch( bitmap.pixel_mode ) {
                default: {
                    mojo_assertf(0, "Font::CreateFromFile()\n -> Pixel mode not supported.\n"); 
                } break;

                case FT_PIXEL_MODE_MONO: {
                    mojo_assertf(0, "Font::CreateFromFile()\n -> TODO: FT_PIXEL_MODE_MONO.\n"); 
                } break;
                
                case FT_PIXEL_MODE_GRAY: {
                    const uint8_t* bm_pixels = (const uint8_t*)bitmap.buffer;

                    for( uint32_t y = 0; y < bitmap.rows; ++y ) {
                        for( uint32_t x = 0; x < bitmap.width; ++x ) bm_buffer[(x + y * bitmap.width) * 4 + 3] = bm_pixels[x];
                        bm_pixels += bitmap.pitch;
                    }
                } break;
            }

            Mojo::Recti packed_rect;
            if( !tex_packer.Pack(bitmap.width, bitmap.rows, 1, bm_buffer, packed_rect) ) {
                Mojo::DebugPrintf(DBG_WARNING, "Font::CreateFromFile()\n -> unable to pack character '%c'\n", i + start_char);              
            }

            glyphs[i].tex_coords[0] = (float)packed_rect.x / atlas_width;
            glyphs[i].tex_coords[1] = (float)packed_rect.y / atlas_height;
            glyphs[i].tex_coords[2] = (float)(packed_rect.x + packed_rect.width) / atlas_width;
            glyphs[i].tex_coords[3] = (float)(packed_rect.y + packed_rect.height) / atlas_height;
        }
        delete[] bm_buffer;

        // Unload the glyphs
        for( uint32_t i = 0; i < num_chars; ++i ) FT_Done_Glyph(ft_glyphs[i]);
        delete[] ft_glyphs;

        FT_Done_Face(ft_face);
        delete[] buffer;

        // Update
        _font_atlas  = tex_atlas.Compile();
        _start_glyph = start_char;
        _num_glyphs  = num_chars;
        _glyphs      = glyphs;
        _base_line   = font_size;
        _line_height = line_height;

        return true;
    }
}