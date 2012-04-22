#ifndef MOJO_COLOR_HPP
#define MOJO_COLOR_HPP

#include <Mojo/Core.hpp>

namespace Mojo
{
    class MOJO_CLASS_EXPORT(Color)
    {
        public:
            Color( const Color& other ) : r(other.r), g(other.g), b(other.b), a(other.a) {}
            Color( const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a  = 255 ) : r(r), g(g), b(b), a(a) {}
            Color& operator=( const Color& other ) { r = other.r; g = other.g; b = other.b; a = other.a; return *this; }

            uint8_t r, g, b, a;
    };
}

#endif /* MOJO_COLOR_HPP */