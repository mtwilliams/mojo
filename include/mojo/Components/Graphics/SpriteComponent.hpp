#ifndef MOJO_COMPONENTS_GRAPHICS_SPRITE_HPP
#define MOJO_COMPONENTS_GRAPHICS_SPRITE_HPP

#include <Mojo/Component.hpp>

namespace Mojo
{
namespace Components
{
    struct MOJO_CLASS_EXPORT(SpriteComponent) : public Mojo::Component, public Mojo::DrawableComponent
    {
        public:
            SpriteComponent()
                : Mojo::Component(Mojo::Component::SPRITE_COMPONENT,
                                  MOJO_COMPONENT_IS_A(Drawable))
            {
            }

            virtual ~SpriteComponent()
            {
            }

            void Draw()
            {
            }

        private:

    };
}
}

#endif /* MOJO_COMPONENTS_GRAPHICS_SPRITE_HPP */