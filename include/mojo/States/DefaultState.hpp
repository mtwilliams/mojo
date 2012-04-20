#ifndef MOJO_STATES_DEFAULT_HPP
#define MOJO_STATES_DEFAULT_HPP

#include <Mojo/State.hpp>

namespace Mojo
{
namespace States
{
    class MOJO_CLASS_EXPORT(Default) : public Mojo::State
    {
        public:
            Default();
            ~Default();

            void Update( const Mojo::Timestep timestep );
            void Draw();
    };
}
}

#endif /* MOJO_STATES_DEFAULT_HPP */