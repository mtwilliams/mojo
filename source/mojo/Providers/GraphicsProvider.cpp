#include <Mojo/Services.hpp>

#include <Mojo/Debug.hpp>
#include <Mojo/Platform/GL.h>

namespace Mojo
{
namespace Services { template <> Mojo::Services::Graphics* Get<Mojo::Services::Graphics>(); }
namespace Providers
{
    class Graphics : public Mojo::Services::Graphics
    {
        private:
            static const uint32_t max_num_callbacks = 16;

        private:
            static int GLFWCALL WindowCloseCallback( void ) {
                Mojo::Providers::Graphics* graphics_provider = (Mojo::Providers::Graphics*)MOJO_GET_SERVICE(Graphics);
                for( uint32_t i = 0; i < graphics_provider->_num_window_closed_callbacks; ++i ) graphics_provider->_window_closed_callbacks[i]();
                return GL_TRUE;
            }

            static void GLFWCALL WindowSizeCallback( int width, int height ) {
                Mojo::Providers::Graphics* graphics_provider = (Mojo::Providers::Graphics*)MOJO_GET_SERVICE(Graphics);
                for( uint32_t i = 0; i < graphics_provider->_num_window_resized_callbacks; ++i ) graphics_provider->_window_resized_callbacks[i]((uint32_t)width, (uint32_t)height);
            }

        public:
            Graphics()
                : _initialized(false)
                , _num_window_closed_callbacks(0)
                , _num_window_resized_callbacks(0)
            {
            }

            ~Graphics()
            {
                Destroy();
            }

            bool Create( const Mojo::Graphics::Settings& settings )
            {
                if( _initialized ) return false;
                if( !glfwInit() ) return false;

                glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
                glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 1);
                glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, settings.no_resize ? GL_TRUE : GL_FALSE);
                glfwOpenWindowHint(GLFW_FSAA_SAMPLES, settings.num_samples);

                if( !glfwOpenWindow(settings.width, settings.height, 8, 8, 8, 0, 24, 8, settings.fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW) ) {
                    glfwTerminate();
                    return false;
                }

                if( glewInit() != GLEW_NO_ERROR ) {
                    glfwTerminate();
                    return false;
                }

                glfwSetWindowTitle(settings.title);
                glfwSetWindowCloseCallback(&WindowCloseCallback);
                glfwSetWindowSizeCallback(&WindowSizeCallback);
                //glfwSetKeyCallback(&KeyCallback);
                //glfwSetCharCallback(&CharCallback);
                //glfwSetMouseButtonCallback(&MouseBtnCallback);
                //glfwSetMousePosCallback(&MousePosCallback);
                //glfwSetMouseWheelCallback(&MouseWheelCallback);
                glfwSwapInterval(settings.vsync ? 1 : 0);

                return true;
            }

            void Destroy()
            {
                if( !_initialized ) return;
                _initialized = false;
                glfwTerminate();
            }

            void Clear( uint32_t clear_targets, float r, float g, float b, float a, float depth = 1.0f, uint32_t stencil = 0, uint32_t buffer = 0 )
            {
                mojo_assertf(buffer == 0, "Not implemented.");

                const bool clear_color = (clear_targets & Mojo::Graphics::CLEAR_COLOR) == Mojo::Graphics::CLEAR_COLOR;
                const bool clear_depth = (clear_targets & Mojo::Graphics::CLEAR_DEPTH) == Mojo::Graphics::CLEAR_DEPTH;
                const bool clear_stencil = (clear_targets & Mojo::Graphics::CLEAR_STENCIL) == Mojo::Graphics::CLEAR_STENCIL;

                uint32_t buffer_bits = 0;

                if( clear_color ) {
                    glClearColor(r, g, b, a);
                    buffer_bits |= GL_COLOR_BUFFER_BIT;
                }

                if( clear_depth ) {
                    glClearDepth(depth);
                    buffer_bits |= GL_DEPTH_BUFFER_BIT;
                }

                if( clear_stencil ) {
                    glClearStencil(stencil);
                    buffer_bits |= GL_STENCIL_BUFFER_BIT;
                }

                glClear(buffer_bits);
            }

            void SwapBuffers()
            {
                // todo: dispatch input MessageQueues
                glfwSwapBuffers();
            }

            void Reference( const Mojo::Graphics::Handle& handle )
            {
            }

            void Dereference( const Mojo::Graphics::Handle& handle )
            {
            }

            uint32_t Register_OnWindowClosed( const Mojo::Graphics::WindowClosedCallback& callback )
            {
                if( _num_window_closed_callbacks >= max_num_callbacks ) return 0xFFFFFFFF;
                const uint32_t id = _num_window_closed_callbacks++;
                _window_closed_callbacks[id] = callback;
                return id;
            }

            void Deregister_OnWindowClosed( uint32_t id )
            {
                if( id >= _num_window_closed_callbacks ) return;
                if( id < _num_window_closed_callbacks - 1 ) _window_closed_callbacks[id] = _window_closed_callbacks[_num_window_closed_callbacks - 1];
                _num_window_closed_callbacks--;
            }

            uint32_t Register_OnWindowResized( const Mojo::Graphics::WindowResizedCallback& callback )
            {
                if( _num_window_resized_callbacks >= max_num_callbacks ) return 0xFFFFFFFF;
                const uint32_t id = _num_window_resized_callbacks++;
                _window_resized_callbacks[id] = callback;
                return id;
            }

            void Deregister_OnWindowResized( uint32_t id )
            {
                if( id >= _num_window_resized_callbacks ) return;
                if( id < _num_window_resized_callbacks - 1 ) _window_resized_callbacks[id] = _window_resized_callbacks[_num_window_resized_callbacks - 1];
                _num_window_resized_callbacks--;
            }

        private:
            bool _initialized;

            uint32_t _num_window_closed_callbacks;
            Mojo::Graphics::WindowClosedCallback _window_closed_callbacks[max_num_callbacks];

            uint32_t _num_window_resized_callbacks;
            Mojo::Graphics::WindowResizedCallback _window_resized_callbacks[max_num_callbacks];
    };
}
namespace Services
{
    template <> Mojo::Services::Graphics* Get<Mojo::Services::Graphics>()
    {
        static Mojo::Providers::Graphics* graphics_provider = new Mojo::Providers::Graphics();
        return (Mojo::Services::Graphics*)graphics_provider;
    }
}
}