#include <Mojo/Services.hpp>
#include <Mojo/Messages.hpp>

#include <Mojo/Debug.hpp>

namespace Mojo
{
namespace Services
{
    template <> Mojo::Services::Input* Get<Mojo::Services::Input>();
}
namespace Providers
{
    class Input : public Mojo::Services::Input
    {
        private:
            static const uint32_t max_num_callbacks = 16;

        public:
            Input()
                : _num_key_pressed_callbacks(0)
                , _num_key_released_callbacks(0)
            {
            }

            ~Input()
            {
            }

            void ProcessMessageBuffer( Mojo::MessageQueue* message_queue )
            {
                while( const Mojo::Message* msg = message_queue->Dequeue() )
                {
                    switch( msg->type ) {
                        case Mojo::Messages::KEY_PRESSED_MSG: {
                            for( uint32_t i = 0; i < _num_key_pressed_callbacks; ++i ) _key_pressed_callbacks[i]((Mojo::Input::Key)((Mojo::Messages::KeyPressed*)msg)->key);
                        } break;

                        case Mojo::Messages::KEY_RELEASED_MSG: {
                            for( uint32_t i = 0; i < _num_key_released_callbacks; ++i ) _key_released_callbacks[i]((Mojo::Input::Key)((Mojo::Messages::KeyReleased*)msg)->key);
                        } break;

                        default: {
                            Mojo::DebugPrintf(DBG_WARNING, "Providers::Input::ProcessMessageBuffer\n -> unknown message %u\n", msg->type);
                        } break;
                    }
                }
            }

            uint32_t Register_OnKeyPressed( const Mojo::Input::KeyPressedCallback& callback )
            {
                if( _num_key_pressed_callbacks >= max_num_callbacks ) return 0xFFFFFFFF;
                const uint32_t id = _num_key_pressed_callbacks++;
                _key_pressed_callbacks[id] = callback;
                return id;
            }

            void Deregister_OnKeyPressed( uint32_t id )
            {
                if( id >= _num_key_pressed_callbacks ) return;
                if( id < _num_key_pressed_callbacks - 1 ) _key_pressed_callbacks[id] = _key_pressed_callbacks[_num_key_pressed_callbacks - 1];
                _num_key_pressed_callbacks--;
            }

            uint32_t Register_OnKeyReleased( const Mojo::Input::KeyReleasedCallback& callback )
            {
                if( _num_key_released_callbacks >= max_num_callbacks ) return 0xFFFFFFFF;
                const uint32_t id = _num_key_released_callbacks++;
                _key_released_callbacks[id] = callback;
                return id;
            }

            void Deregister_OnKeyReleased( uint32_t id )
            {
                if( id >= _num_key_released_callbacks ) return;
                if( id < _num_key_released_callbacks - 1 ) _key_released_callbacks[id] = _key_released_callbacks[_num_key_released_callbacks - 1];
                _num_key_released_callbacks--;
            }

        private:
            uint32_t _num_key_pressed_callbacks;
            Mojo::Input::KeyPressedCallback _key_pressed_callbacks[max_num_callbacks];

            uint32_t _num_key_released_callbacks;
            Mojo::Input::KeyReleasedCallback _key_released_callbacks[max_num_callbacks];
    };
}
namespace Services
{
    template <> Mojo::Services::Input* Get<Mojo::Services::Input>()
    {
        static Mojo::Providers::Input* input_provider = new Mojo::Providers::Input();
        return (Mojo::Services::Input*)input_provider;
    }
}
}