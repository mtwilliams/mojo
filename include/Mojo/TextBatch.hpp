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

#endif /* MOJO_TEXT_BATCH_HPP */