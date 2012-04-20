#ifndef MOJO_CORE_COMPILER_HPP
#define MOJO_CORE_COMPILER_HPP

// Microsoft Visual Studio:
#ifdef _MSC_VER
    #define MOJO_MSVC_BUILD
#endif

// GCC:
#ifdef __GNUC__
    #define MOJO_GCC_BUILD
#endif

// Clang:
#ifdef __clang__
    #define MOJO_CLANG_BUILD
#endif

#endif /* MOJO_CORE_COMPILER_HPP */