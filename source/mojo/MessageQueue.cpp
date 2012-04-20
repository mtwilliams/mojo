#include <Mojo/MessageQueue.hpp>

#include <Mojo/Debug.hpp>

#include <string.h>

namespace Mojo
{
    // todo: circular/ring

    MessageQueue::MessageQueue( size_t size )
        : _size(size)
        , _enqueue_pos(0)
        , _dequeue_pos(0)
        , _buffer(new uint8_t[size])
    {
    }

    MessageQueue::~MessageQueue()
    {
        delete[] _buffer;
    }

    void MessageQueue::Enqueue( const Mojo::Message* msg )
    {
        if( msg->size + _enqueue_pos > _size - 1 ) Mojo::DebugPrintf(DBG_WARNING, "MessageQueue::Enqueue\n -> overflow; tried to queue %hu, %hu\n", msg->type, msg->size);
        memcpy((void*)&_buffer[_enqueue_pos], (void*)msg, msg->size);
        _enqueue_pos += msg->size;
    }

    const Mojo::Message* MessageQueue::Dequeue()
    {
        if( _dequeue_pos == _enqueue_pos ) return NULL;
        const Mojo::Message* msg = (const Mojo::Message*)_buffer[_dequeue_pos];
        _dequeue_pos += msg->size;
        if( _dequeue_pos = _enqueue_pos ) _dequeue_pos = 0; _enqueue_pos = 0;
        return msg;
    }
}