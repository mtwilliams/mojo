#ifndef MOJO_MESSAGE_HPP
#define MOJO_MESSAGE_HPP

#include <Mojo/Core.hpp>

namespace Mojo
{
    struct MOJO_CLASS_EXPORT(Message)
    {
        uint16_t type, size;
        Message( uint16_t type, uint16_t size ) : type(type), size(size) {}
    };
}

#endif /* MOJO_MESSAGE_HPP */