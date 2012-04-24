#ifndef MOJO_FONT_HPP
#define MOJO_FONT_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Graphics.hpp>

namespace Mojo
{
    class TextBatch;
    class MOJO_CLASS_EXPORT(Font) : public Mojo::NonCopyable
    {
        friend class Mojo::TextBatch;

        private:
            struct Glyph {
                float tex_coords[4]; // min x, min y, max x, max y
                float width, height, advance;
                float offs_x, offs_y;
            };

        public:
            Font();
            ~Font();

            bool CreateFromFile( const char* path, const uint32_t font_size, const uint32_t start_char = 32, const size_t num_chars = 96, const uint32_t atlas_width = 256, const uint32_t atlas_height = 256 );

        private:
            float GetLineHeight() const { return _line_height; }
            const Glyph& GetGlyph( const uint32_t glyph ) const { return _glyphs[glyph - _start_glyph]; }
            float GetGlyphAdvance( const uint32_t glyph ) const { return _glyphs[glyph - _start_glyph].advance; }

        private:
            uint32_t _start_glyph;
            uint32_t _num_glyphs;
            float _line_height;
            Glyph* _glyphs;

            Mojo::Texture _font_atlas;
    };
}

#endif /* MOJO_FONT_HPP */