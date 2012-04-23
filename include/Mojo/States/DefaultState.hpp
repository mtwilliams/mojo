#ifndef MOJO_STATES_DEFAULT_HPP
#define MOJO_STATES_DEFAULT_HPP

#include <Mojo/State.hpp>
#include <Mojo/Graphics.hpp>

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

        private:
            Mojo::Texture _cube_wireframe;
    };
}
}

#endif /* MOJO_STATES_DEFAULT_HPP */