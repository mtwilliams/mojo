#ifndef MOJO_SERVICES_GRAPHICS_HPP
#define MOJO_SERVICES_GRAPHICS_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Graphics.hpp>

#define MOJO_GRAPHICS_REGISTER_CALLBACK( event, callback ) Mojo::Services::Get<Mojo::Services::Graphics>()->Register_##event(callback);
#define MOJO_GRAPHICS_DEREGISTER_CALLBACK( event, id ) Mojo::Services::Get<Mojo::Services::Graphics>()->Deregister_##event(id);

namespace Mojo
{
namespace Graphics
{
    enum ClearTarget {
        CLEAR_COLOR   = (1 << 0),
        CLEAR_DEPTH   = (1 << 1),
        CLEAR_STENCIL = (1 << 2),
    };

    struct MOJO_CLASS_EXPORT(Settings) {
        const char* title;
        uint32_t width, height;
        uint32_t num_samples;
        unsigned vsync      : 1;
        unsigned fullscreen : 1;
        unsigned no_resize  : 1;
        unsigned reserved   : 5;
    };

    typedef Mojo::Delegate0<void> WindowClosedCallback;
    typedef Mojo::Delegate2<void, uint32_t, uint32_t> WindowResizedCallback;
}

namespace Services
{
    class Graphics : public Mojo::NonCopyable
    {
        public:
            virtual ~Graphics() {}

            virtual bool Create( const Mojo::Graphics::Settings& settings ) = 0;
            virtual void Destroy() = 0;
            
            virtual void Clear( uint32_t clear_targets, float r, float g, float b, float a, float depth = 1.0f, uint32_t stencil = 0, uint32_t buffer = 0 ) = 0;
            virtual void SwapBuffers() = 0;

            virtual void Reference( const Mojo::Graphics::Handle& handle ) = 0;
            virtual void Dereference( const Mojo::Graphics::Handle& handle ) = 0;

            virtual uint32_t Register_OnWindowClosed( const Mojo::Graphics::WindowClosedCallback& callback ) = 0;
            virtual void Deregister_OnWindowClosed( uint32_t id ) = 0;

            virtual uint32_t Register_OnWindowResized( const Mojo::Graphics::WindowResizedCallback& callback ) = 0;
            virtual void Deregister_OnWindowResized( uint32_t id ) = 0;
    };
}
}

#endif /* MOJO_SERVICES_GRAPHICS_HPP */