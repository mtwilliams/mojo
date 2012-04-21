#ifndef MOJO_GRAPHICS_HPP
#define MOJO_GRAPHICS_HPP

#include <Mojo/Core.hpp>

namespace Mojo
{
namespace Graphics
{
    struct MOJO_CLASS_EXPORT(Handle) {
        enum Type {
            TEXTURE       = 1,
            SHADER        = 2,
            RENDER_TARGET = 3,
        };

        unsigned valid : 1;
        unsigned type  : 3;
        unsigned id    : 12;

        Handle( unsigned type, unsigned id, unsigned valid = 1 );
        ~Handle();

        static Handle invalid;
    };
}
    typedef Mojo::Graphics::Handle Texture, Shader, RenderTarget;
}

#endif /* MOJO_GRAPHICS_HPP */