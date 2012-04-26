#ifndef MOJO_UI_CANVAS_HPP
#define MOJO_UI_CANVAS_HPP

#include <Mojo/UI/Control.hpp>
#include <Mojo/UI/Skin.hpp>

namespace Mojo
{
namespace UI
{
    class MOJO_CLASS_EXPORT(Canvas) : public Mojo::UI::Control
    {
        public:
            Canvas( const Mojo::UI::Skin* skin )
                : _skin(skin)
            {
            }

            ~Canvas()
            {
            }



        private:
            const Mojo::UI::Skin* _skin;
    };
}
}

#endif /* MOJO_UI_CANVAS_HPP */