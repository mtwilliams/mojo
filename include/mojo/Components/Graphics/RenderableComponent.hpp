#ifndef MOJO_COMPONENTS_GRAPHICS_RENDERABLE_HPP
#define MOJO_COMPONENTS_GRAPHICS_RENDERABLE_HPP

#include <Mojo/Component.hpp>

namespace Mojo
{
namespace Components
{
    struct MOJO_CLASS_EXPORT(RenderableComponent) : public Mojo::Component
    {
        public:
            enum Type {
                SPRITE_RENDERABLE = 1,
            };

        public:
            RenderableComponent( const Mojo::Components::RenderableComponent::Type renderable_type )
                : Mojo::Component(RENDERABLE_COMPONENT)
                , _renderable_type(renderable_type)
            {
            }

            virtual ~RenderableComponent()
            {
            }

        public:
            inline Mojo::Components::RenderableComponent::Type GetRenderableType() const { return _renderable_type; }

        private:
            const Mojo::Components::RenderableComponent::Type _renderable_type;
    };
}
}

#endif /* MOJO_COMPONENTS_GRAPHICS_RENDERABLE_HPP */