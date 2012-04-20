#ifndef MOJO_DEBUG_HPP
#define MOJO_DEBUG_HPP

#include <Mojo/Core.hpp>

namespace Mojo
{
    enum DebugLevel {
        DBG_INFO         = 1,
        DBG_WARNING      = 2,
        DBG_ERROR        = 3,
        DBG_DEPRECATED   = 4,
        DBG_CATASTROPHIC = 5,
    };

    MOJO_EXPORT(void DebugPrintf( const DebugLevel dbg_level, const char* format, ... ));
}

#endif /* MOJO_DEBUG_HPP */