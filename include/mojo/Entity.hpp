#ifndef MOJO_ENTITY_HPP
#define MOJO_ENTITY_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Component.hpp>

namespace Mojo
{
    class MOJO_CLASS_EXPORT(Entity) : public Mojo::NonCopyable
    {
        public:
            Entity();
            ~Entity();

            void AttachComponent( Mojo::Component* component );
            void DetachComponent( Mojo::Component* component );
            void GetComponent( const Mojo::Component::Type component_type );


        private:
            static const uint32_t max_num_components = 8;

            uint32_t _num_components;
            Mojo::Component* _components[max_num_components];
    };
}

#endif /* MOJO_ENTITY_HPP */