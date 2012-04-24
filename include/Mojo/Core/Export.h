#ifndef MOJO_CORE_EXPORT_HPP
#define MOJO_CORE_EXPORT_HPP

#include <Mojo/Core/Types.h>
#include <Mojo/Core/Compiler.h>

#ifdef MOJO_STATIC_BUILD
    #define MOJO_EXPORT(x) extern x
    #define MOJO_CLASS_EXPORT(x) x
    #define MOJO_INTERNAL_EXPORT(x) x
#else
    #if defined(MOJO_MSVC_BUILD)
        #ifdef MOJO_BUILD
            #define MOJO_EXPORT(x) extern __declspec(dllexport) x
            #define MOJO_CLASS_EXPORT(x) __declspec(dllexport) x
            #define MOJO_INTERNAL_EXPORT(x) __declspec(dllexport) x
        #else
            #define MOJO_EXPORT(x) extern __declspec(dllimport) x
            #define MOJO_CLASS_EXPORT(x) __declspec(dllimport) x
            #define MOJO_INTERNAL_EXPORT(x) x
        #endif
    #elif defined(MOJO_GCC_BUILD)
        #define MOJO_EXPORT(x) extern x
        #define MOJO_CLASS_EXPORT(x) x
        #define MOJO_INTERNAL_EXPORT(x) x
    #else
        #error Compiler not supported.
    #endif
#endif

#endif /* MOJO_CORE_EXPORT_H */