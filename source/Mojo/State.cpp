#ifndef MOJO_STATE_HPP
#define MOJO_STATE_HPP

#include <Mojo/Core.hpp>

namespace Mojo
{
    class MOJO_CLASS_EXPORT(State) : public Mojo::NonCopyable
    {
        public:
            virtual ~State()
            {
            }

        public:
            virtual void Update( const Mojo::Timestep timestep ) = 0;
            virtual void Draw() = 0;
    };

namespace States
{
    static const uint32_t max_num_states = 16;
    static uint32_t num_states = 0;
    static Mojo::State* states[max_num_states];

    Mojo::State* GetCurrentState()
    {
        if( num_states == 0 ) return NULL;
        return states[num_states - 1];
    }

    void Push( Mojo::State* state )
    {
        if( num_states >= max_num_states ) return;
        states[num_states++] = state;
    }

    void Pop()
    {
        if( num_states == 0 ) return;
        num_states--;
    }
}
}

#endif /* MOJO_STATE_HPP */