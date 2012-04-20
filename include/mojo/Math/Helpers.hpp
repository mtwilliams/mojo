#ifndef MOJO_MATH_HELPERS_HPP
#define MOJO_MATH_HELPERS_HPP

#include <Mojo/Core.hpp>

namespace Mojo
{
    static const float  f_pi = 3.14159265358979323846f;
    static const double d_pi = 3.14159265358979323846;

    inline float RadiansToDegrees( const float rad ) { return rad * (180.0f / f_pi); }
    inline float DegressToRadians( const float deg ) { return deg * (f_pi / 180.0f); }

    inline double RadiansToDegrees( const double rad ) { return rad * (180.0 / d_pi); }
    inline double DegressToRadians( const double deg ) { return deg * (d_pi / 180.0); }

    inline float SmoothStep( const float min, const float max, float t ) { t = Clamp((t - min) / (max - min), 0.0f, 1.0f); return (t * t * (3.0f - 2.0f * t)); }
    inline double SmoothStep( const double min, const double max, double t ) { t = Clamp((t - min) / (max - min), 0.0, 1.0); return (t * t * (3.0 - 2.0 * t)); }
}

#endif /* MOJO_MATH_HELPERS_HPP */