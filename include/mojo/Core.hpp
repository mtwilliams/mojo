#ifndef MOJO_CORE_HPP
#define MOJO_CORE_HPP

#include <Mojo/Core/Compiler.hpp>
#include <Mojo/Core/Environment.hpp>

#include <Mojo/Core/Types.hpp>
#include <Mojo/Core/Export.hpp>

#include <Mojo/Core/Assert.hpp>
#include <Mojo/Core/Delegate.hpp>

#include <Mojo/Core/NonCopyable.hpp>

namespace Mojo
{
    typedef float Timestep;

    template <typename T> inline void Swap( T& a, T& b ) { T c(a); a = b; b = c; }
}

#endif /* MOJO_CORE_HPP */