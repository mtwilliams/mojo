#ifndef MOJO_MATH_HPP
#define MOJO_MATH_HPP

#include <Mojo/Math/Helpers.hpp>
#include <Mojo/Math/Vector2.hpp>
#include <Mojo/Math/Vector3.hpp>
#include <Mojo/Math/Vector4.hpp>
#include <Mojo/Math/Matrix4.hpp>
#include <Mojo/Math/Rectangle.hpp>

namespace Mojo
{
    typedef Mojo::Vector2<int>   Vector2i;
    typedef Mojo::Vector2<float> Vector2f;

    typedef Mojo::Vector3<int>   Vector3i;
    typedef Mojo::Vector3<float> Vector3f;

    typedef Mojo::Vector3<int>   Vector4i;
    typedef Mojo::Vector4<float> Vector4f;

    typedef Mojo::Matrix4<float> Matrix4f;

    typedef Mojo::Rect<float> Rectf;
    typedef Mojo::Rect<int>   Recti;
}

#endif /* MOJO_MATH_HPP */