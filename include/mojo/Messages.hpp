#ifndef MOJO_MESSAGES_HPP
#define MOJO_MESSAGES_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Message.hpp>

namespace Mojo
{
namespace Messages
{
    enum Type {
        // Input
        KEY_PRESSED_MSG  = 1,
        KEY_RELEASED_MSG = 2,
    };

    struct MOJO_CLASS_EXPORT(KeyPressed) : public Mojo::Message {
        uint32_t key;
        KeyPressed() : Mojo::Message(KEY_PRESSED_MSG, sizeof(KeyPressed)) {}
    };

    struct MOJO_CLASS_EXPORT(KeyReleased) : public Mojo::Message {
        uint32_t key;
        KeyReleased() : Mojo::Message(KEY_RELEASED_MSG, sizeof(KeyReleased)) {}
    };
}
}

#endif /* MOJO_MESSAGES_HPP */