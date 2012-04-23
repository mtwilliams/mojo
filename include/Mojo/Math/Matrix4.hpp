#ifndef MOJO_MATH_MATRIX4_HPP
#define MOJO_MATH_MATRIX4_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Math/Helpers.hpp>
#include <Mojo/Math/Vector3.hpp>

namespace Mojo
{
    template <typename T>
    class MOJO_CLASS_EXPORT(Matrix4)
    {
        public: /* constants */
            static const Matrix4<T> identity;

        public: /* external */
            Matrix4()
            {
                static const T im[] = {
                    1.0, 0.0, 0.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0
                };

                memcpy((void*)&_m[0], (void*)&im[0], 16 * sizeof(T));
            }

            Matrix4( const T* m )
            {
                memcpy((void*)&_m, (void*)m, 16 * sizeof(T));
            }

            Matrix4( const Matrix4<T>& other )
            {
                memcpy((void*)&_m, (void*)other._m, 16 * sizeof(T));
            }

            Matrix4<T>& operator=( const Matrix4<T>& other )
            {
                memcpy((void*)&_m, (void*)other._m, 16 * sizeof(T));
                return *this;
            }

            Matrix4<T> operator*( const Matrix4<T>& other )
            {
                Matrix4<T> result;

                result._m[0]  = _m[0]  * other._m[0] + _m[1]  * other._m[4] + _m[2]  * other._m[8]  + _m[3]  * other._m[12];
                result._m[1]  = _m[0]  * other._m[1] + _m[1]  * other._m[5] + _m[2]  * other._m[9]  + _m[3]  * other._m[13];
                result._m[2]  = _m[0]  * other._m[2] + _m[1]  * other._m[6] + _m[2]  * other._m[10] + _m[3]  * other._m[14];
                result._m[3]  = _m[0]  * other._m[3] + _m[1]  * other._m[7] + _m[2]  * other._m[11] + _m[3]  * other._m[15];
                result._m[4]  = _m[4]  * other._m[0] + _m[5]  * other._m[4] + _m[6]  * other._m[8]  + _m[7]  * other._m[12];
                result._m[5]  = _m[4]  * other._m[1] + _m[5]  * other._m[5] + _m[6]  * other._m[9]  + _m[7]  * other._m[13];
                result._m[6]  = _m[4]  * other._m[2] + _m[5]  * other._m[6] + _m[6]  * other._m[10] + _m[7]  * other._m[14];
                result._m[7]  = _m[4]  * other._m[3] + _m[5]  * other._m[7] + _m[6]  * other._m[11] + _m[7]  * other._m[15];
                result._m[8]  = _m[8]  * other._m[0] + _m[9]  * other._m[4] + _m[10] * other._m[8]  + _m[11] * other._m[12];
                result._m[9]  = _m[8]  * other._m[1] + _m[9]  * other._m[5] + _m[10] * other._m[9]  + _m[11] * other._m[13];
                result._m[10] = _m[8]  * other._m[2] + _m[9]  * other._m[6] + _m[10] * other._m[10] + _m[11] * other._m[14];
                result._m[11] = _m[8]  * other._m[3] + _m[9]  * other._m[7] + _m[10] * other._m[11] + _m[11] * other._m[15];
                result._m[12] = _m[12] * other._m[0] + _m[13] * other._m[4] + _m[14] * other._m[8]  + _m[15] * other._m[12];
                result._m[13] = _m[12] * other._m[1] + _m[13] * other._m[5] + _m[14] * other._m[9]  + _m[15] * other._m[13];
                result._m[14] = _m[12] * other._m[2] + _m[13] * other._m[6] + _m[14] * other._m[10] + _m[15] * other._m[14];
                result._m[15] = _m[12] * other._m[3] + _m[13] * other._m[7] + _m[14] * other._m[11] + _m[15] * other._m[15];

                return result;
            }

            inline Matrix4<T>& operator*=( const Matrix4<T>& other ) { *this = (*this) * other; return *this; }

            Vector3<T> operator*( const Vector3<T>& vec )
            {
                return Vector3<T>(
                    vec.x * _m[0] + vec.y * _m[1] + vec.z * _m[2] + _m[3],
                    vec.y * _m[4] + vec.y * _m[5] + vec.z * _m[6] + _m[7],
                    vec.z * _m[8] + vec.y * _m[9] + vec.z * _m[10] + _m[11]
                );
            }

            void Translate( const Vector3<T>& vec )
            {
                const T tm[] = {
                    1.0, 0.0, 0.0, vec.x,
                    0.0, 1.0, 0.0, vec.y,
                    0.0, 0.0, 1.0, vec.z,
                    0.0, 0.0, 0.0, 1.0
                };

                *this *= Matrix4<T>(&tm[0]);
            }

            void Scale( const Vector3<T>& vec )
            {
                const T sm[] = {
                    vec.x, 0.0, 0.0, 0.0,
                    0.0, vec.y, 0.0, 0.0,
                    0.0, 0.0, vec.z, 0.0,
                    0.0, 0.0, 0.0, 1.0
                };

                *this *= Matrix4<T>(&sm[0]);
            }

            void Rotate( const Vector3<T>& vec )
            {
                // todo: pre-multiply seperate matrices?
                const T rxm[] = {
                    1.0, 0.0, 0.0, 0.0,
                    0.0, cos(vec.x), -sin(vec.x), 0.0,
                    0.0, sin(vec.x), cos(vec.x), 0.0,
                    0.0, 0.0, 0.0, 1.0
                };

                const T rym[] = {
                    cos(vec.y), 0.0, sin(vec.y), 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    -sin(vec.y), 0.0, cos(vec.y), 0.0,
                    0.0, 0.0, 0.0, 1.0
                };

                const T rzm[] = {
                    cos(vec.z), sin(vec.z), 0.0, 0.0,
                    -sin(vec.z), cos(vec.z), 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0
                };


                *this *= Matrix4<T>(&rxm[0]) * Matrix4<T>(&rym[0]) * Matrix4<T>(&rzm[0]);
            }

            static Matrix4<T> Ortho( float left, float right, float top, float bottom, float near, float far )
            {
                const T om[] = {
                    2.0 / (right - left), 0.0, 0.0, -(right + left) / (right - left),
                    0.0, 2.0 / (top - bottom), 0.0, -(top + bottom) / (top - bottom),
                    0.0, 0.0, -2.0 / (far - near), -(far + near) / (far - near),
                    0.0, 0.0, 0.0f, 1.0
                };

                return Matrix4<T>(&om[0]);
            }

            static Matrix4<T> Perspective( float fov, float aspect_ratio, float near, float far )
            {
                T f = 1.0 / tan(fov / 2.0);
                const T pm[] = {
                    f / aspect_ratio, 0.0, 0.0, 0.0,
                    0.0, f, 0.0, 0.0,
                    0.0, 0.0, (far + near) / (near - far), (2.0 * far * near) / (near - far),
                    0.0, 0.0, -1.0, 0.0
                };

                return Matrix4<T>(&pm[0]);
            }

            static Matrix4<T> LookAt( const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& up )
            {
                Vector3<T> f = (target - eye).Normalized();
                Vector3<T> nup = up.Normalized();
                Vector3<T> s = f.Cross(nup);
                Vector3<T> u = s.Cross(f);

                const T lm[] = {
                    s.x, s.y, s.z, 0.0,
                    u.x, u.y, u.z, 0.0,
                    -f.x, -f.y, -f.z, 0.0,
                    0.0, 0.0, 0.0, 1.0
                };

                Matrix4 m = Matrix4<T>(&lm[0]);
                m.Translate(-eye);

                return m;
            }

            inline operator const T*() const { return &_m[0]; }

        private: /* internal */
            T _m[16];
    };

    template <typename T>
    const Matrix4<T> Matrix4<T>::identity = Matrix4<T>();
}

#endif /* MOJO_MATH_MATRIX4_HPP */