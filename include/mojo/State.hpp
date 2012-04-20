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
    MOJO_EXPORT(Mojo::State* GetCurrentState());
    MOJO_EXPORT(void Push( Mojo::State* state ));
    MOJO_EXPORT(void Pop());
}
}

#endif /* MOJO_STATE_HPP */