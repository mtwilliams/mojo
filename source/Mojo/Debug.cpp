#include <Mojo/Debug.hpp>

#include <stdio.h>
#include <stdarg.h>

namespace Mojo
{
    void DebugPrintf( const DebugLevel dbg_level, const char* format, ... )
    {
        va_list vargs;

        switch( dbg_level ) {
            case DBG_INFO:         /* printf("Info: "); */   break;
            case DBG_WARNING:      printf("Warning: ");      break;
            case DBG_ERROR:        printf("Error: ");        break;
            case DBG_DEPRECATED:   printf("Deprecated: ");   break;
            case DBG_CATASTROPHIC: printf("Catastrophic: "); break;
        }

        va_start(vargs, format);
        vprintf(format, vargs);
        va_end(vargs);
    }
}