#ifndef MOJO_CORE_HPP
#define MOJO_CORE_HPP

#include <Mojo/Core/Compiler.hpp>
#include <Mojo/Core/Environment.hpp>

#include <Mojo/Core/Types.hpp>
#include <Mojo/Core/Export.hpp>

#include <Mojo/Core/Assert.hpp>
#include <Mojo/Core/Delegate.hpp>

#include <Mojo/Core/NonCopyable.hpp>

#include <float.h>
#include <math.h>
#include <string.h>

namespace Mojo
{
    typedef float Timestep;

    template <typename T> inline void Swap( T& a, T& b ) { T c(a); a = b; b = c; }

    inline bool Compare( const float a, const float b )   { return fabs(a - b) < FLT_EPSILON; }
    inline bool Compare( const double a, const double b ) { return fabs(a - b) < DBL_EPSILON; }

    template <typename T>
    inline T Clamp( const T x, const T min, const T max ) { return (x < min) ? min : (x > max) ? max : x; }
}

#endif /* MOJO_CORE_HPP */