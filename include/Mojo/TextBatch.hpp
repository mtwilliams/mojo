#ifndef MOJO_TEXT_BATCH_HPP
#define MOJO_TEXT_BATCH_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Math.hpp>
#include <Mojo/Graphics.hpp>
#include <Mojo/Batch.hpp>
#include <Mojo/Font.hpp>

namespace Mojo
{
    class MOJO_CLASS_EXPORT(TextBatch) : protected Mojo::Batch
    {
        public:
            TextBatch( size_t num_characters );
            ~TextBatch();

            void Begin( const Mojo::Font& font );
            void End();

            void Draw( const char* text, const Mojo::Vector3f position, const Mojo::Color& color = Mojo::Colors::White );

        private:
            bool _in_batch;
            const Mojo::Font* _font;
    };
}

// static const Mojo::Rectf text_dim = arial->Measure("Hello, World");
// text_batch->Draw("Hello, World!", Mojo::Vector2f((800.0f - text_dim.width) / 2.0f, (600.0f - text_dim.height) / 2.0f));

#endif /* MOJO_TEXT_BATCH_HPP */