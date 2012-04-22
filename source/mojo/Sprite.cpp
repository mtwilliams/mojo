#include <Mojo/Sprite.hpp>
#include <Mojo/Services.hpp>

namespace Mojo
{
    Sprite::Sprite( uint32_t num_frames, const Mojo::Sprite::Frame* frames )
        : _num_frames(num_frames)
        , _frames(new Mojo::Sprite::Frame[num_frames])
    {
        memcpy((void*)_frames, (void*)frames, num_frames * sizeof(Mojo::Sprite::Frame));
    }

    Sprite::~Sprite()
    {
        delete[] _frames;
    }
}