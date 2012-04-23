#ifndef MOJO_MATH_VECTOR3_HPP
#define MOJO_MATH_VECTOR3_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Math/Helpers.hpp>
#include <Mojo/Math/Vector2.hpp>

namespace Mojo
{
    template <typename T>
    class MOJO_CLASS_EXPORT(Vector3)
    {
        public: /* external */
            Vector3() : x(0), y(0), z(0) {}
            Vector3( T x, T y, T z ) : x(x), y(y), z(z) {}
            Vector3( const Vector2<T>& other ) : x(other.x), y(other.y), z(0) {}
            Vector3( const Vector3<T>& other ) : x(other.x), y(other.y), z(other.z) {}
            Vector3& operator=( const Vector3<T>& other ) { x = other.x; y = other.y; z = other.z; return *this; }

            // Vector3<T> and Vector3<T>
            inline Vector3<T> operator+( const Vector3<T>& other ) const { return Vector3<T>(x + other.x, y + other.y, z + other.z); }
            inline Vector3<T> operator-( const Vector3<T>& other ) const { return Vector3<T>(x - other.x, y - other.y, z - other.z); }
            inline Vector3<T> operator*( const Vector3<T>& other ) const { return Vector3<T>(x * other.x, y * other.y, z * other.z); }
            inline Vector3<T> operator/( const Vector3<T>& other ) const { return Vector3<T>(x / other.x, y / other.y, z / other.z); }

            inline Vector3<T>& operator+=( const Vector3<T>& other ) const { x += other.x; y += other.y; z += other.z; return *this; }
            inline Vector3<T>& operator-=( const Vector3<T>& other ) const { x -= other.x; y -= other.y; z -= other.z; return *this; }
            inline Vector3<T>& operator*=( const Vector3<T>& other ) const { x *= other.x; y *= other.y; z *= other.z; return *this; }
            inline Vector3<T>& operator/=( const Vector3<T>& other ) const { x /= other.x; y /= other.y; z /= other.z; return *this; }

            // Vector3<T> and T
            inline Vector3<T> operator*( T scalar ) const { return Vector3<T>(x * scalar, y * scalar, z * scalar); }
            inline Vector3<T> operator/( T scalar ) const { return Vector3<T>(x / scalar, y / scalar, z / scalar); }
            inline Vector3<T>& operator*=( T scalar ) const { x *= scalar; y *= scalar; z *= scalar; return *this; }
            inline Vector3<T>& operator/=( T scalar ) const { x /= scalar; y /= scalar; z /= scalar; return *this; }

            // Comparision
            inline bool operator==( const Vector3<float>& other ) { return Mojo::Compare(x, other.x) && Mojo::Compare(y, other.y) && Mojo::Compare(z, other.z); }
            inline bool operator!=( const Vector3<float>& other ) { return (!Mojo::Compare(x, other.x)) || (!Mojo::Compare(y, other.y)) || (!Mojo::Compare(z, other.z)); }

            // Helpers
            inline T Dot( const Vector3<T>& other ) const { return (x * other.x + y * other.y + z * other.z); }
            inline Vector3<T> Cross( const Vector3<T>& other ) const { return Vector3<T>(y * other.z - other.y * z, z * other.x - other.z * x, x * other.y - other.x * y); }
            inline T Magnitude() const { return sqrt(x * x + y * y + z * z); }
            inline void Normalize() { const T rm = (T)1 / Magnitude(); x *= rm; y *= rm; z *= rm; }
            inline Vector3<T> Normalized() const { const T rm = (T)1 / Magnitude(); return Vector3<T>(x * rm, y * rm, z * rm); }
            inline Vector3<T> Lerp( const Vector3<T>& a, const Vector3<T>& b, const T t ) { return a + (b - a) * t; }
            inline Vector3<T> SmoothStep( const Vector3<T>& a, const Vector3<T>& b, const T t ) { return Lerp(a, b, Mojo::SmoothStep(0, 1, t)); }

        public: /* external */
            union {
                struct { T x, y, z; };
                struct { T u, v, w; };
                struct { T r, g, b; };
                struct { T xyz[3]; };
                struct { T uvw[3]; };
                struct { T rgb[3]; };
            };
    };
}

#endif /* MOJO_MATH_VECTOR3_HPP */