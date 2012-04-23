#ifndef MOJO_SERVICES_INPUT_HPP
#define MOJO_SERVICES_INPUT_HPP

#include <Mojo/Core.hpp>
#include <Mojo/MessageQueue.hpp>

#define MOJO_INPUT_REGISTER_CALLBACK( event, callback ) Mojo::Services::Get<Mojo::Services::Input>()->Register_##event(callback);
#define MOJO_INPUT_DEREGISTER_CALLBACK( event, id ) Mojo::Services::Get<Mojo::Services::Input>()->Deregister_##event(id);

namespace Mojo
{
namespace Input
{
    enum Key {
        KEY_UNKNOWN      = -1,
        KEY_SPACE        = 32,
        KEY_SPECIAL      = 256,
        KEY_ESC          = (KEY_SPECIAL + 1),
        KEY_F1           = (KEY_SPECIAL + 2),
        KEY_F2           = (KEY_SPECIAL + 3),
        KEY_F3           = (KEY_SPECIAL + 4),
        KEY_F4           = (KEY_SPECIAL + 5),
        KEY_F5           = (KEY_SPECIAL + 6),
        KEY_F6           = (KEY_SPECIAL + 7),
        KEY_F7           = (KEY_SPECIAL + 8),
        KEY_F8           = (KEY_SPECIAL + 9),
        KEY_F9           = (KEY_SPECIAL + 10),
        KEY_F10          = (KEY_SPECIAL + 11),
        KEY_F11          = (KEY_SPECIAL + 12),
        KEY_F12          = (KEY_SPECIAL + 13),
        KEY_F13          = (KEY_SPECIAL + 14),
        KEY_F14          = (KEY_SPECIAL + 15),
        KEY_F15          = (KEY_SPECIAL + 16),
        KEY_F16          = (KEY_SPECIAL + 17),
        KEY_F17          = (KEY_SPECIAL + 18),
        KEY_F18          = (KEY_SPECIAL + 19),
        KEY_F19          = (KEY_SPECIAL + 20),
        KEY_F20          = (KEY_SPECIAL + 21),
        KEY_F21          = (KEY_SPECIAL + 22),
        KEY_F22          = (KEY_SPECIAL + 23),
        KEY_F23          = (KEY_SPECIAL + 24),
        KEY_F24          = (KEY_SPECIAL + 25),
        KEY_F25          = (KEY_SPECIAL + 26),
        KEY_UP           = (KEY_SPECIAL + 27),
        KEY_DOWN         = (KEY_SPECIAL + 28),
        KEY_LEFT         = (KEY_SPECIAL + 29),
        KEY_RIGHT        = (KEY_SPECIAL + 30),
        KEY_LSHIFT       = (KEY_SPECIAL + 31),
        KEY_RSHIFT       = (KEY_SPECIAL + 32),
        KEY_LCTRL        = (KEY_SPECIAL + 33),
        KEY_RCTRL        = (KEY_SPECIAL + 34),
        KEY_LALT         = (KEY_SPECIAL + 35),
        KEY_RALT         = (KEY_SPECIAL + 36),
        KEY_TAB          = (KEY_SPECIAL + 37),
        KEY_ENTER        = (KEY_SPECIAL + 38),
        KEY_BACKSPACE    = (KEY_SPECIAL + 39),
        KEY_INSERT       = (KEY_SPECIAL + 40),
        KEY_DEL          = (KEY_SPECIAL + 41),
        KEY_PAGEUP       = (KEY_SPECIAL + 42),
        KEY_PAGEDOWN     = (KEY_SPECIAL + 43),
        KEY_HOME         = (KEY_SPECIAL + 44),
        KEY_END          = (KEY_SPECIAL + 45),
        KEY_KP_0         = (KEY_SPECIAL + 46),
        KEY_KP_1         = (KEY_SPECIAL + 47),
        KEY_KP_2         = (KEY_SPECIAL + 48),
        KEY_KP_3         = (KEY_SPECIAL + 49),
        KEY_KP_4         = (KEY_SPECIAL + 50),
        KEY_KP_5         = (KEY_SPECIAL + 51),
        KEY_KP_6         = (KEY_SPECIAL + 52),
        KEY_KP_7         = (KEY_SPECIAL + 53),
        KEY_KP_8         = (KEY_SPECIAL + 54),
        KEY_KP_9         = (KEY_SPECIAL + 55),
        KEY_KP_DIVIDE    = (KEY_SPECIAL + 56),
        KEY_KP_MULTIPLY  = (KEY_SPECIAL + 57),
        KEY_KP_SUBTRACT  = (KEY_SPECIAL + 58),
        KEY_KP_ADD       = (KEY_SPECIAL + 59),
        KEY_KP_DECIMAL   = (KEY_SPECIAL + 60),
        KEY_KP_EQUAL     = (KEY_SPECIAL + 61),
        KEY_KP_ENTER     = (KEY_SPECIAL + 62),
        KEY_KP_NUM_LOCK  = (KEY_SPECIAL + 63),
        KEY_CAPS_LOCK    = (KEY_SPECIAL + 64),
        KEY_SCROLL_LOCK  = (KEY_SPECIAL + 65),
        KEY_PAUSE        = (KEY_SPECIAL + 66),
        KEY_LSUPER       = (KEY_SPECIAL + 67),
        KEY_RSUPER       = (KEY_SPECIAL + 68),
        KEY_MENU         = (KEY_SPECIAL + 69),
        KEY_LAST
    };

    typedef Mojo::Delegate1<void, Key> KeyPressedCallback;
    typedef Mojo::Delegate1<void, Key> KeyReleasedCallback;
}
namespace Services
{
    class Input : public Mojo::NonCopyable
    {
        public:
            virtual ~Input() {}
            virtual void ProcessMessageBuffer( Mojo::MessageQueue* message_queue ) = 0;
            
            virtual uint32_t Register_OnKeyPressed( const Mojo::Input::KeyPressedCallback& callback ) = 0;
            virtual void Deregister_OnKeyPressed( uint32_t id ) = 0;

            virtual uint32_t Register_OnKeyReleased( const Mojo::Input::KeyReleasedCallback& callback ) = 0;
            virtual void Deregister_OnKeyReleased( uint32_t id ) = 0;
    };
}
}

#endif /* MOJO_SERVICES_INPUT_HPP */