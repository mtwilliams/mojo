#ifndef MOJO_MESSAGE_QUEUE_HPP
#define MOJO_MESSAGE_QUEUE_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Message.hpp>

namespace Mojo
{
    class MOJO_CLASS_EXPORT(MessageQueue) : public Mojo::NonCopyable
    {
        public:
            MessageQueue( size_t size );
            ~MessageQueue();

            void Enqueue( const Mojo::Message* msg );
            const Mojo::Message* Dequeue();

        private:
            const size_t _size;
            uint32_t _enqueue_pos, _dequeue_pos;
            uint8_t* _buffer;
    };
}

#endif /* MOJO_MESSAGE_QUEUE_HPP */