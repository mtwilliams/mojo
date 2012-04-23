#ifndef MOJO_MATH_VECTOR4_HPP
#define MOJO_MATH_VECTOR4_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Math/Helpers.hpp>
#include <Mojo/Math/Vector3.hpp>

namespace Mojo
{
    template <typename T>
    class MOJO_CLASS_EXPORT(Vector4)
    {
        public: /* external */
            Vector4() : x(0), y(0), z(0), w(0) {}
            Vector4( T x, T y, T z, T w ) : x(x), y(y), z(z), w(w) {}
            Vector4( const Vector3<T>& other ) : x(other.x), y(other.y), z(other.z), w(0) {}
            Vector4( const Vector4<T>& other ) : x(other.x), y(other.y), z(other.z), w(other.w) {}
            Vector4& operator=( const Vector4<T>& other ) { x = other.x; y = other.y; z = other.z; w = other.w; return *this; }

            // Vector4<T> and Vector4<T>
            inline Vector4<T> operator+( const Vector4<T>& other ) const { return Vector4<T>(x + other.x, y + other.y, z + other.z, w + other.w); }
            inline Vector4<T> operator-( const Vector4<T>& other ) const { return Vector4<T>(x - other.x, y - other.y, z - other.z, w - other.w); }
            inline Vector4<T> operator*( const Vector4<T>& other ) const { return Vector4<T>(x * other.x, y * other.y, z * other.z, w * other.w); }
            inline Vector4<T> operator/( const Vector4<T>& other ) const { return Vector4<T>(x / other.x, y / other.y, z / other.z, w / other.w); }

            inline Vector4<T>& operator+=( const Vector4<T>& other ) const { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
            inline Vector4<T>& operator-=( const Vector4<T>& other ) const { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
            inline Vector4<T>& operator*=( const Vector4<T>& other ) const { x *= other.x; y *= other.y; z *= other.z; w *= other.w; return *this; }
            inline Vector4<T>& operator/=( const Vector4<T>& other ) const { x /= other.x; y /= other.y; z /= other.z; w /= other.w; return *this; }

            // Vector4<T> and T
            inline Vector4<T> operator*( T scalar ) const { return Vector4<T>(x * scalar, y * scalar, z * scalar, w * scalar); }
            inline Vector4<T> operator/( T scalar ) const { return Vector4<T>(x / scalar, y / scalar, z / scalar, w / scalar); }
            inline Vector4<T>& operator*=( T scalar ) const { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
            inline Vector4<T>& operator/=( T scalar ) const { x /= scalar; y /= scalar; z /= scalar; w /= scalar; return *this; }

            // Comparision
            inline bool operator==( const Vector4<float>& other ) { return Mojo::Compare(x, other.x) && Mojo::Compare(y, other.y) && Mojo::Compare(z, other.z) && Mojo::Compare(w, other.w); }
            inline bool operator!=( const Vector4<float>& other ) { return (!Mojo::Compare(x, other.x)) || (!Mojo::Compare(y, other.y)) || (!Mojo::Compare(z, other.z)); }

            // Helpers
            inline T Dot( const Vector4<T>& other ) const { return (x * other.x + y * other.y + z * other.z + w * other.w); }
            inline T Magnitude() const { return sqrt(x * x + y * y + z * z + w * w); }
            inline void Normalize() { const T rm = (T)1 / Magnitude(); x *= rm; y *= rm; z *= rm; w *= rm; }
            inline Vector4<T> Normalized() const { const T rm = (T)1 / Magnitude(); return Vector4<T>(x * rm, y * rm, z * rm, w * rm); }
            inline Vector4<T> Lerp( const Vector4<T>& a, const Vector4<T>& b, const T t ) { return a + (b - a) * t; }
            inline Vector4<T> SmoothStep( const Vector4<T>& a, const Vector4<T>& b, const T t ) { return Lerp(a, b, Mojo::SmoothStep(0, 1, t)); }

        public: /* external */
            union {
                struct { T x, y, z, w; };
                struct { T r, g, b, a; };
                struct { T xyzw[4]; };
                struct { T rgba[4]; };
            };
    };
}

#endif /* MOJO_MATH_VECTOR4_HPP */