#ifndef MOJO_SPRITE_HPP
#define MOJO_SPRITE_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Graphics.hpp>

namespace Mojo
{
    class MOJO_CLASS_EXPORT(Sprite) : public Mojo::NonCopyable
    {
        public:
            struct Frame {
                uint32_t x, y;
                uint32_t width, height;
            };

        public:
            Sprite( uint32_t num_frames, const Mojo::Sprite::Frame* frames );
            ~Sprite();

            const Mojo::Sprite::Frame GetFrame( uint32_t frame ) const
            {
                mojo_assertf(frame < _num_frames, "Out-of-bounds.\n");
                return _frames[frame];
            }

        private:
            const uint32_t _num_frames;
            Mojo::Sprite::Frame* _frames;
    };
}

#endif /* MOJO_SPRITE_HPP */