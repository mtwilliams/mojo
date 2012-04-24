#include <Mojo/Font.hpp>
#include <Mojo/Services.hpp>

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

    Mojo::Rectf Font::Measure( const char* str ) const
    {
        // todo:
        return Mojo::Rectf(0.0f, 0.0f, 0.0f, 0.0f);
    }

    bool Font::CreateFromFile( const char* path, const uint32_t font_size, const uint32_t start_char, const size_t num_chars, const uint32_t atlas_width, const uint32_t atlas_height )
    {
        if( !path || font_size == 0 || num_chars == 0 || _num_glyphs > 0 || atlas_width == 0 || atlas_height == 0 ) return false;

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

        FT_Face face;
        if( FT_New_Memory_Face(Mojo::GetFreeTypeLibrary(), (const FT_Byte*)buffer, file_len, 0, &face) ) {
            delete[] buffer;
            return false;
        }

        FT_Set_Char_Size(face, font_size * 64, font_size * 64, 96, 96);

        uint32_t atlas_x = 0, atlas_y = 0;
        const uint32_t atlas_pitch = atlas_width * 4;
        uint8_t* atlas_pixels = new uint8_t[atlas_width * atlas_height * 4];
        memset((void*)atlas_pixels, 255, atlas_width * atlas_height * 4);

        Mojo::Font::Glyph* glyphs = new Mojo::Font::Glyph[num_chars];

        uint32_t max_glyph_height = 0, max_row_height = 0;
        const uint32_t end_char = start_char + num_chars;
        for( uint32_t ch = start_char; ch < end_char; ++ch ) {
            // todo: check for errors

            FT_Glyph glyph;
            FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT);
            FT_Get_Glyph(face->glyph, &glyph);

            const float advance = face->glyph->advance.x >> 6;

            FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, 0, 1);
            FT_BitmapGlyph bm_glyph = (FT_BitmapGlyph)glyph;
            FT_Bitmap bitmap = bm_glyph->bitmap;

            const int32_t  bm_width  = bitmap.width;
            const int32_t  bm_height = bitmap.rows;
            const uint8_t* bm_pixels = bitmap.buffer;
            const float offs_x = bm_glyph->left;
            const float offs_y = bm_glyph->top;

            max_row_height = max_row_height < bm_height ? bm_height : max_row_height;
            max_glyph_height = max_glyph_height < bm_height ? bm_height : max_glyph_height;

            if( atlas_x + bm_width > atlas_width ) {
                atlas_x = 0;
                atlas_y += max_row_height;
                max_row_height = 0;
            }

            if( atlas_y + bm_height > atlas_height ) {
                FT_Done_Face(face);
                delete[] atlas_pixels;
                delete[] buffer;
                delete[] glyphs;
                return false;
            }

            

            Mojo::Font::Glyph& _glyph = glyphs[ch - start_char];
            _glyph.tex_coords[0] = (float)atlas_x / (float)atlas_width;
            _glyph.tex_coords[1] = (float)atlas_y / (float)atlas_height;
            _glyph.tex_coords[2] = (float)(atlas_x + bm_width) / (float)atlas_width;
            _glyph.tex_coords[3] = (float)(atlas_y + bm_height) / (float)atlas_height;
            _glyph.width   = bm_width;
            _glyph.height  = bm_height;
            _glyph.advance = advance;
            _glyph.offs_x  = offs_x;
            _glyph.offs_y  = offs_y;

            uint8_t* atlas_offs = atlas_pixels + (atlas_x + atlas_y * atlas_width) * 4;
            switch( bitmap.pixel_mode ) {
                default: {
                    for( uint32_t y = 0; y < bm_height; ++y ) {
                        for( uint32_t x = 0; x < bm_width; ++x ) {
                            atlas_offs[x * 4 + 3] = bm_pixels[x];
                        }

                        bm_pixels += bitmap.pitch;
                        atlas_offs += atlas_pitch;
                    }
                } break;
            }

            atlas_x += bm_width;
        }

        _start_glyph = start_char;
        _num_glyphs  = num_chars;
        _line_height = max_glyph_height;
        _glyphs      = glyphs;
        _font_atlas  = MOJO_GET_SERVICE(Graphics)->CreateTexture2D(atlas_width, atlas_height, Mojo::Graphics::TF_RGBA8, (const void*)atlas_pixels, true);

        FT_Done_Face(face);
        delete[] atlas_pixels;
        delete[] buffer;
        return true;
    }
}