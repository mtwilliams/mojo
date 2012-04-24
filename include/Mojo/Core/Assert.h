#ifndef MOJO_CORE_ASSERT_H
#define MOJO_CORE_ASSERT_H

#include <stdio.h>
#include <stdlib.h>

#ifdef MOJO_DEBUG_BUILD
    #define mojo_stringify( x ) mojo_stringify_internal(x)
    #define mojo_stringify_internal( x ) #x
    #define mojo_assertf( condition, format, ... ) { if( !(condition) ) { fprintf(stderr, format, ##__VA_ARGS__); fprintf(stderr, "\n" #condition " failed on " mojo_stringify(__LINE__) " in " mojo_stringify(__FILE__)); abort();} }
#else
    #define mojo_assertf( condition, format, ... )
#endif

#endif /* MOJO_CORE_ASSERT_H */