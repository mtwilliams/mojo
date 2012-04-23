#ifndef MOJO_COMPONENT_HPP
#define MOJO_COMPONENT_HPP

#include <Mojo/Core.hpp>

#define MOJO_COMPONENT_IS_A( capability ) Mojo::Component::capability##_FLAG
#define MOJO_COMPONENT_IS( component, capability ) component->GetFlag(Mojo::Component::capability##_FLAG)

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
                SPRITE_COMPONENT              = GRAPHICS_BASE_COMPONENT + 1,

                PHYSICS_BASE_COMPONENT        = 400,
                PHYS_BODY_COMPONENT           = PHYSICS_BASE_COMPONENT + 1,

                USER_BASE_COMPONENT           = 1000,
            };

            enum Flags {
                Updateable_FLAG = (1 << 0),
                Drawable_FLAG   = (1 << 1),
            };

        public:
            Component( const Mojo::Component::Type type, const uint32_t flags )
                : _type(type)
                , _flags(flags)
            {
            }

            virtual ~Component()
            {
            }

        public:
            inline Mojo::Component::Type GetType() const { return (Mojo::Component::Type)_type; }
            inline bool GetFlag( const uint32_t flag ) const { return (_flags & flag) == flag; }

        private:
            const unsigned _flags : 8;
            const unsigned _type  : 24;
    };

    class MOJO_CLASS_EXPORT(UpdateableComponent)
    {
        public:
            virtual ~UpdateableComponent();
            virtual void Update( const Mojo::Timestep timestep ) = 0;
    };

    class MOJO_CLASS_EXPORT(DrawableComponent)
    {
        public:
            virtual ~DrawableComponent();
            virtual void Draw() = 0;
    };
}

#endif /* MOJO_COMPONENT_HPP */