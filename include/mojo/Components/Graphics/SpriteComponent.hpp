#ifndef MOJO_COMPONENTS_GRAPHICS_SPRITE_HPP
#define MOJO_COMPONENTS_GRAPHICS_SPRITE_HPP

#include <Mojo/Components/Graphics/RenderableComponent.hpp>

namespace Mojo
{
namespace Components
{
    struct MOJO_CLASS_EXPORT(SpriteComponent) : public Mojo::Components::RenderableComponent
    {
        public:
            SpriteComponent()
                : Mojo::Components::RenderableComponent(Mojo::Components::RenderableComponent::SPRITE_RENDERABLE)
            {
            }

            virtual ~SpriteComponent()
            {
            }

        private:
    };
}
}

#endif /* MOJO_COMPONENTS_GRAPHICS_SPRITE_HPP */