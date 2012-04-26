#ifndef MOJO_CORE_HPP
#define MOJO_CORE_HPP

#include <Mojo/Core/Compiler.h>
#include <Mojo/Core/Environment.h>

#include <Mojo/Core/Types.h>
#include <Mojo/Core/Export.h>

#include <Mojo/Core/Assert.h>
#include <Mojo/Core/Delegate.hpp>

#include <Mojo/Core/NonCopyable.hpp>

#include <float.h>
#include <math.h>
#include <string.h>

namespace Mojo
{
    typedef float Timestep;

    template <typename T> inline void Swap( T& a, T& b ) { T c(a); a = b; b = c; }

    template <typename T>
    inline bool Compare( const T a, const T b ) { return a == b };

    template <>
    inline bool Compare<float>( const float a, const float b )   { return fabs(a - b) < FLT_EPSILON; }

    template <>
    inline bool Compare<double>( const double a, const double b ) { return fabs(a - b) < DBL_EPSILON; }

    template <typename T>
    inline T Clamp( const T x, const T min, const T max ) { return (x < min) ? min : (x > max) ? max : x; }
}

#endif /* MOJO_CORE_HPP */