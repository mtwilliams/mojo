#ifndef MOJO_FONT_HPP
#define MOJO_FONT_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Math.hpp>
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
                float x_advance, y_advance;
                float x_bearing, y_bearing;
            };

        public:
            Font();
            ~Font();

            bool CreateFromFile( const char* path, const uint32_t font_size, const uint32_t start_char = 32, const size_t num_chars = 96 );

            Mojo::Rectf Measure( const char* string );

        public:
            float GetLineHeight() const { return _line_height; }

        private:
            Mojo::Texture _font_atlas;
            uint32_t _start_glyph;
            uint32_t _num_glyphs;
            Glyph*   _glyphs;

            float _base_line;
            float _line_height;
    };
}

#endif /* MOJO_FONT_HPP */