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

    bool Font::CreateFromFile( const char* path, const uint32_t font_size, const uint32_t start_char, const size_t num_chars )
    {
        if( !path || font_size == 0 || num_chars == 0 || _num_glyphs > 0 ) return false;

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
            uint32_t num_bytes_read = file_len;
            while( num_bytes_read > 0 ) {
                size_t read = filesystem->Read(file, file_len - num_bytes_read, (void*)&buffer[num_bytes_read]);
                mojo_assertf(read > 0, "Font::CreateFromFile\n -> Services/Filesystem error?\n");
                num_bytes_read -= read;
            }
        }

        filesystem->Close(file);

        FT_Face face;
        if( FT_New_Memory_Face(Mojo::GetFreeTypeLibrary(), (const FT_Byte*)buffer, file_len, 0, &face) ) {
            delete[] buffer;
            return false;
        }

        FT_Set_Char_Size(face, font_size * 64, font_size * 64, 96, 96);

        static const struct { uint32_t a, w, h; } fa_lut[] = {
            {  64 *  64,  64,  64 }, {  64 * 128,  64, 128 },
            { 128 * 128, 128, 128 }, { 128 * 256, 128, 256 },
            { 256 * 256, 256, 256 }, { 256 * 512, 256, 512 },
            { 512 * 512, 512, 512 }
        };

        const uint32_t apx_glyph_width   = /* todo */ 0;
        const uint32_t apx_glyph_height  = /* todo */ 0;
        const uint32_t apx_required_area = /* todo */ 0;

        uint32_t atlas_width = 0, atlas_height = 0;
        for( uint32_t i = 0; i < 7; ++i ) {
            if( apx_required_area > fa_lut[i].a ) continue;
            atlas_width = fa_lut[i].w; atlas_height = fa_lut[i].h;
            break;
        }

        if( atlas_width == 0 || atlas_height == 0 ) {
            FT_Done_Face(face);
            delete[] buffer;
            return false;
        }

        uint8_t* bm_buffer = new uint8_t[apx_glyph_width * apx_glyph_height * 4];

        const uint32_t end_char = start_char + num_chars;
        for( uint32_t ch = start_char; ch < end_char; ++ch ) {
            // todo: check for errors

            FT_Glyph glyph;
            FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT);
            FT_Get_Glyph(face->glyph, &glyph);
            FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, 0, 1);
            FT_BitmapGlyph bm_glyph = (FT_BitmapGlyph)glyph;
            FT_Bitmap bitmap = bm_glyph->bitmap;

            const int32_t bm_width = bitmap.width;
            const int32_t bm_height = bitmap.rows;


        }

        FT_Done_Face(face);
        delete[] bm_buffer;
        delete[] buffer;

        return false;
    }
}