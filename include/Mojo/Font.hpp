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
                float tex_coords[4];
                float width, height;
            };

        public:
            Font();
            ~Font();

            bool CreateFromFile( const char* path, const uint32_t font_size, const uint32_t start_char = 32, const size_t num_chars = 96 );

        private:
            float GetLineHeight() const { return _line_height; }
            const Glyph& GetGlyph( const uint32_t glyph ) const { return _glyphs[glyph - _start_glyph]; }
            float GetGlyphOffset( const uint32_t glyph ) const { return _glyphs[glyph - _start_glyph].width; }

        private:
            uint32_t _start_glyph;
            uint32_t _num_glyphs;
            float _line_height;
            Glyph* _glyphs;

            Mojo::Texture _font_atlas;
    };
}

#endif /* MOJO_FONT_HPP */