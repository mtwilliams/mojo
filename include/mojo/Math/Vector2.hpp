#ifndef MOJO_MATH_VECTOR2_HPP
#define MOJO_MATH_VECTOR2_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Math/Helpers.hpp>

namespace Mojo
{
    template <typename T>
    class MOJO_CLASS_EXPORT(Vector2)
    {
        public: /* external */
            Vector2() : x(0), y(0) {}
            Vector2( T x, T y ) : x(x), y(y) {}
            Vector2( const Vector2<T>& other ) : x(other.x), y(other.y) {}
            Vector2& operator=( const Vector2<T>& other ) { x = other.x; y = other.y; return *this; }

            // Vector2<T> and Vector2<T>
            inline Vector2<T> operator+( const Vector2<T>& other ) const { return Vector2<T>(x + other.x, y + other.y); }
            inline Vector2<T> operator-( const Vector2<T>& other ) const { return Vector2<T>(x - other.x, y - other.y); }
            inline Vector2<T> operator*( const Vector2<T>& other ) const { return Vector2<T>(x * other.x, y * other.y); }
            inline Vector2<T> operator/( const Vector2<T>& other ) const { return Vector2<T>(x / other.x, y / other.y); }

            inline Vector2<T>& operator+=( const Vector2<T>& other ) const { x += other.x; y += other.y; return *this; }
            inline Vector2<T>& operator-=( const Vector2<T>& other ) const { x -= other.x; y -= other.y; return *this; }
            inline Vector2<T>& operator*=( const Vector2<T>& other ) const { x *= other.x; y *= other.y; return *this; }
            inline Vector2<T>& operator/=( const Vector2<T>& other ) const { x /= other.x; y /= other.y; return *this; }

            // Vector2<T> and T
            inline Vector2<T> operator*( T scalar ) const { return Vector2<T>(x * scalar, y * scalar); }
            inline Vector2<T> operator/( T scalar ) const { return Vector2<T>(x / scalar, y / scalar); }
            inline Vector2<T>& operator*=( T scalar ) const { x *= scalar; y *= scalar; return *this; }
            inline Vector2<T>& operator/=( T scalar ) const { x /= scalar; y /= scalar; return *this; }

            // Comparision
            inline bool operator==( const Vector2<float>& other ) { return Mojo::Compare(x, other.x) && Mojo::Compare(y, other.y); }
            inline bool operator!=( const Vector2<float>& other ) { return (!Mojo::Compare(x, other.x)) || (!Mojo::Compare(y, other.y)); }

            // Helpers
            inline T Dot( const Vector2<T>& other ) const { return (x * other.x + y * other.y); }
            inline T Magnitude() const { return sqrt(x * x + y * y); }
            inline void Normalize() { const T rm = (T)1 / Magnitude(); x *= rm; y *= rm; }
            inline Vector2<T> Normalized() const { const T rm = (T)1 / Magnitude(); return Vector2<T>(x * rm, y * rm); }
            inline Vector2<T> Lerp( const Vector2<T>& a, const Vector2<T>& b, const T t ) { return a + (b - a) * t; }
            inline Vector2<T> SmoothStep( const Vector2<T>& a, const Vector2<T>& b, const T t ) { return Lerp(a, b, Mojo::SmoothStep(0, 1, t)); }

        public: /* external */
            union {
                struct { T x, y; };
                struct { T u, v; };
            };
    };
}

#endif /* MOJO_MATH_VECTOR2_HPP */