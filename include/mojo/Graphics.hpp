#ifndef MOJO_GRAPHICS_HPP
#define MOJO_GRAPHICS_HPP

#include <Mojo/Core.hpp>

namespace Mojo
{
namespace Graphics
{
    struct MOJO_CLASS_EXPORT(Handle) {
        unsigned type : 4;
        unsigned id   : 12;

        Handle( unsigned type, unsigned id );
        ~Handle();
    };
}
    typedef Mojo::Graphics::Handle Texture, Shader, RenderTarget;
}

#endif /* MOJO_GRAPHICS_HPP */