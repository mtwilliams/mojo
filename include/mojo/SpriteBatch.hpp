#ifndef MOJO_SPRITE_BATCH_HPP
#define MOJO_SPRITE_BATCH_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Math.hpp>
#include <Mojo/Graphics.hpp>
#include <Mojo/Batch.hpp>
#include <Mojo/Sprite.hpp>

namespace Mojo
{
    class MOJO_CLASS_EXPORT(SpriteBatch) : protected Mojo::Batch
    {
        public:
            SpriteBatch( size_t num_sprites );
            ~SpriteBatch();

            void Begin( const Mojo::Texture& sprite_sheet );
            void End();

            void Draw( const Mojo::Sprite& sprite, uint32_t frame, const Mojo::Vector3f position, const Mojo::Vector2f& scale = Mojo::Vector2f(1.0f, 1.0f), const Mojo::Color& color = Mojo::Colors::White );

        private:
            bool _in_batch;
            Mojo::Texture _sprite_sheet;
            uint32_t _sprite_sheet_width, _sprite_sheet_height;
    };
}

#endif /* MOJO_SPRITE_BATCH_HPP */