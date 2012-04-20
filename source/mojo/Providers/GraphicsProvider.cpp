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
                , _model_matrix(Mojo::Matrix4f::identity)
                , _view_matrix(Mojo::Matrix4f::identity)
                , _projection_matrix(Mojo::Matrix4f::identity)
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

                glViewport(0, 0, settings.width, settings.height);

                return true;
            }

            void Destroy()
            {
                if( !_initialized ) return;
                _initialized = false;
                glfwTerminate();
            }

            uint32_t Width()
            {
                int width, height;
                glfwGetWindowSize(&width, &height);
                return (uint32_t)width;
            }

            uint32_t Height()
            {
                int width, height;
                glfwGetWindowSize(&width, &height);
                return (uint32_t)height;
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

            void SetMatrix( const Mojo::Graphics::MatrixType matrix_type, const Mojo::Matrix4f& matrix )
            {
                using namespace Mojo::Graphics;

                switch( matrix_type ) {
                    case MATRIX_MODEL:      _model_matrix = matrix; glMatrixMode(GL_MODELVIEW); glLoadTransposeMatrixf((const float*)(_view_matrix * _model_matrix)); break;
                    case MATRIX_VIEW:       _view_matrix = matrix;  glMatrixMode(GL_MODELVIEW); glLoadTransposeMatrixf((const float*)(_view_matrix * _model_matrix)); break;
                    case MATRIX_PROJECTION: _projection_matrix = matrix; glMatrixMode(GL_PROJECTION); glLoadTransposeMatrixf((const float*)(_projection_matrix)); break;
                }
            }

            void Enable( const Mojo::Graphics::ArrayType array_type )
            {
                using namespace Mojo::Graphics;

                GLenum cap;
                switch( array_type ) {
                    case VERTEX_ARRAY:    cap = GL_VERTEX_ARRAY; break;
                    case INDEX_ARRAY:     cap = GL_INDEX_ARRAY; break;
                    case COLOR_ARRAY:     cap = GL_COLOR_ARRAY; break;
                    case TEX_COORD_ARRAY: cap = GL_TEXTURE_COORD_ARRAY; break;
                }

                glEnableClientState(cap);
            }

            void Disable( const Mojo::Graphics::ArrayType array_type )
            {
                using namespace Mojo::Graphics;

                GLenum cap;
                switch( array_type ) {
                    case VERTEX_ARRAY:    cap = GL_VERTEX_ARRAY; break;
                    case INDEX_ARRAY:     cap = GL_INDEX_ARRAY; break;
                    case COLOR_ARRAY:     cap = GL_COLOR_ARRAY; break;
                    case TEX_COORD_ARRAY: cap = GL_TEXTURE_COORD_ARRAY; break;
                }

                glDisableClientState(cap);
            }

            void SetInterleavedArrays( const Mojo::Graphics::VertexFormat vertex_format, size_t stride, const void* data )
            {
                using namespace Mojo::Graphics;

                GLenum glformat;
                switch( vertex_format ) {
                    case VT_V2F:             glformat = GL_V2F; break;
                    case VT_V3F:             glformat = GL_V3F; break;
                    case VT_C4UB_V2F:        glformat = GL_C4UB_V2F; break;
                    case VT_C4UB_V3F:        glformat = GL_C4UB_V3F; break;
                    case VT_C3F_V3F:         glformat = GL_C3F_V3F; break;
                    case VT_N3F_V3F:         glformat = GL_N3F_V3F; break;
                    case VT_C4F_N3F_V3F:     glformat = GL_C4F_N3F_V3F; break;
                    case VT_T2F_V3F:         glformat = GL_T2F_V3F; break;
                    case VT_T4F_V4F:         glformat = GL_T4F_V4F; break;
                    case VT_T2F_C4UB_V3F:    glformat = GL_T2F_C4UB_V3F; break;
                    case VT_T2F_C3F_V3F:     glformat = GL_T2F_C3F_V3F; break;
                    case VT_T2F_N3F_V3F:     glformat = GL_T2F_N3F_V3F; break;
                    case VT_T2F_C4F_N3F_V3F: glformat = GL_T2F_C4F_N3F_V3F; break;
                    case VT_T4F_C4F_N3F_V4F: glformat = GL_T4F_C4F_N3F_V4F; break;
                }

                glInterleavedArrays(glformat, stride, data);
            }

            void Draw( const Mojo::Graphics::PrimitiveTopology prim_topology, uint32_t first, size_t count )
            {
                using namespace Mojo::Graphics;

                GLenum mode;
                switch( prim_topology ) {
                    case PRIMITIVE_TOPOLOGY_POINTLIST:     mode = GL_POINTS; break;
                    case PRIMITIVE_TOPOLOGY_LINELIST:      mode = GL_LINES; break;
                    case PRIMITIVE_TOPOLOGY_LINESTRIP:     mode = GL_LINE_STRIP; break;
                    case PRIMITIVE_TOPOLOGY_TRIANGLELIST:  mode = GL_TRIANGLES; break;
                    case PRIMITIVE_TOPOLOGY_TRIANGLESTRIP: mode = GL_TRIANGLE_STRIP; break;
                }

                glDrawArrays(mode, (GLint)first, (GLsizei)count);
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

            Mojo::Matrix4f _model_matrix, _view_matrix, _projection_matrix;
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