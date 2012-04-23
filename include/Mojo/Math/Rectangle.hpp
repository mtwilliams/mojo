#ifndef MOJO_MATH_RECTANGLE_HPP
#define MOJO_MATH_RECTANGLE_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Math/Helpers.hpp>

namespace Mojo
{
    template <typename T>
    class MOJO_CLASS_EXPORT(Rect)
    {
        public: /* external */
            Rect() : x(0), y(0), width(0), height(0) {}
            Rect( T x, T y, T width, T height ) : x(x), y(y), width(width), height(height) {}
            Rect( const Rect<T>& other ) : x(other.x), y(other.y), width(other.width), height(other.height) {}
            Rect<T>& operator=( const Rect<T>& other ) { x = other.x; y = other.y; width = other.width; height = other.height; return *this; }

            T x, y, width, height;
    };
}

#endif /* MOJO_MATH_RECTANGLE_HPP */