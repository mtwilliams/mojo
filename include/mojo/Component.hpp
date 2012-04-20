#ifndef MOJO_COMPONENT_HPP
#define MOJO_COMPONENT_HPP

#include <Mojo/Core.hpp>

namespace Mojo
{
    struct MOJO_CLASS_EXPORT(Component) : public Mojo::NonCopyable
    {
        public:
            enum Type {
                CONTROLLERS_BASE_COMPONENT    = 100,
                KEYBOARD_CONTROLLER_COMPONENT = CONTROLLERS_BASE_COMPONENT + 1,

                AUDIO_BASE_COMPONENT          = 200,
                AUDIO_EMITTER_COMPONENT       = AUDIO_BASE_COMPONENT + 1,

                GRAPHICS_BASE_COMPONENT       = 300,
                RENDERABLE_COMPONENT          = GRAPHICS_BASE_COMPONENT + 1,

                PHYSICS_BASE_COMPONENT        = 400,
                PHYS_BODY_COMPONENT           = PHYSICS_BASE_COMPONENT + 1,

                USER_BASE_COMPONENT           = 1000,
            };

        public:
            Component( const Mojo::Component::Type type )
                : _type(type)
            {
            }

            virtual ~Component()
            {
            }

        public:
            inline Mojo::Component::Type GetType() const { return _type; }

        private:
            const Mojo::Component::Type _type;
    };
}

#endif /* MOJO_COMPONENT_HPP */