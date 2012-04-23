#include <Mojo/Services.hpp>

#include <Mojo/Debug.hpp>
#include <Mojo/Messages.hpp>
#include <Mojo/Platform/GL.h>

// todo: remove/replace stl
#include <map>

#include <FreeImage.h>

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

            static void GLFWCALL KeyCallback( int key, int action ) {
                Mojo::Providers::Graphics* graphics_provider = (Mojo::Providers::Graphics*)MOJO_GET_SERVICE(Graphics);

                if( action == GLFW_PRESS ) {
                    Mojo::Messages::KeyPressed msg;
                    msg.key = key;
                    graphics_provider->_input_messages.Enqueue(&msg);
                } else {
                    Mojo::Messages::KeyReleased msg;
                    msg.key = key;
                    graphics_provider->_input_messages.Enqueue(&msg);
                }
            }

            static void GLFWCALL CharCallback( int key, int action ) {
                Mojo::Providers::Graphics* graphics_provider = (Mojo::Providers::Graphics*)MOJO_GET_SERVICE(Graphics);
            }

            static void GLFWCALL MouseBtnCallback( int button, int action ) {
                Mojo::Providers::Graphics* graphics_provider = (Mojo::Providers::Graphics*)MOJO_GET_SERVICE(Graphics);

                if( action == GLFW_PRESS ) {
                    // Mojo::Messages::MouseBtnPressed msg;
                } else {
                    // Mojo::Messages::MouseBtnReleased msg;
                }
            }

            static void GLFWCALL MousePosCallback( int x, int y ) {
                Mojo::Providers::Graphics* graphics_provider = (Mojo::Providers::Graphics*)MOJO_GET_SERVICE(Graphics);
            }

            static void GLFWCALL MouseWheelCallback( int wheel ) {
                Mojo::Providers::Graphics* graphics_provider = (Mojo::Providers::Graphics*)MOJO_GET_SERVICE(Graphics);
            }

        public:
            Graphics()
                : _initialized(false)
                , _input_messages(1024)
                , _num_window_closed_callbacks(0)
                , _num_window_resized_callbacks(0)
                , _model_matrix(Mojo::Matrix4f::identity)
                , _view_matrix(Mojo::Matrix4f::identity)
                , _projection_matrix(Mojo::Matrix4f::identity)
                , _next_texture_id(1)
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
                glfwSetKeyCallback(&KeyCallback);
                glfwSetCharCallback(&CharCallback);
                glfwSetMouseButtonCallback(&MouseBtnCallback);
                glfwSetMousePosCallback(&MousePosCallback);
                glfwSetMouseWheelCallback(&MouseWheelCallback);
                glfwSwapInterval(settings.vsync ? 1 : 0);

                glEnable(GL_BLEND);
                glEnable(GL_DEPTH_TEST);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glViewport(0, 0, settings.width, settings.height);

                _initialized = true;
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

            void Clear( uint32_t clear_targets, const Mojo::Color& color, float depth = 1.0f, uint32_t stencil = 0, uint32_t buffer = 0 )
            {
                mojo_assertf(buffer == 0, "Not implemented.");

                const bool clear_color = (clear_targets & Mojo::Graphics::CLEAR_COLOR) == Mojo::Graphics::CLEAR_COLOR;
                const bool clear_depth = (clear_targets & Mojo::Graphics::CLEAR_DEPTH) == Mojo::Graphics::CLEAR_DEPTH;
                const bool clear_stencil = (clear_targets & Mojo::Graphics::CLEAR_STENCIL) == Mojo::Graphics::CLEAR_STENCIL;

                uint32_t buffer_bits = 0;

                if( clear_color ) {
                    glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
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
                glfwSwapBuffers();

                MOJO_GET_SERVICE(Input)->ProcessMessageBuffer(&_input_messages);
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

            void Enable( const Mojo::Graphics::State state )
            {
                using namespace Mojo::Graphics;

                GLenum cap;
                switch( state ) {
                    case BLEND: cap = GL_BLEND; break;
                    case DEPTH_TEST: cap = GL_DEPTH_TEST; break;
                }

                glEnable(cap);
            }

            void Disable( const Mojo::Graphics::State state )
            {
                using namespace Mojo::Graphics;

                GLenum cap;
                switch( state ) {
                    case BLEND: cap = GL_BLEND; break;
                    case DEPTH_TEST: cap = GL_DEPTH_TEST; break;
                }

                glDisable(cap);
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

            void SetBlendOp( const Mojo::Graphics::BlendOp blend_op )
            {
                using namespace Mojo::Graphics;

                GLenum mode;
                switch( blend_op ) {
                    case BLEND_OP_ADD: mode = GL_FUNC_ADD; break;
                    case BLEND_OP_SUBTRACT: mode = GL_FUNC_SUBTRACT; break;
                    case BLEND_OP_REV_SUBTRACT: mode = GL_FUNC_REVERSE_SUBTRACT; break;
                    case BLEND_OP_MIN: mode = GL_MIN; break;
                    case BLEND_OP_MAX: mode = GL_MAX; break;
                }

                glBlendEquation(mode);
            }

            void SetBlendFunc( const Mojo::Graphics::BlendFunc src, const Mojo::Graphics::BlendFunc dest )
            {
                using namespace Mojo::Graphics;

                GLenum sfactor, dfactor;
                switch( src ) {
                    case BLEND_ZERO:             sfactor = GL_ZERO; break;
                    case BLEND_ONE:              sfactor = GL_ONE; break;
                    case BLEND_SRC_COLOR:        sfactor = GL_SRC_COLOR; break;
                    case BLEND_INV_SRC_COLOR:    sfactor = GL_ONE_MINUS_SRC_COLOR; break;
                    case BLEND_SRC_ALPHA:        sfactor = GL_SRC_ALPHA; break;
                    case BLEND_INV_SRC_ALPHA:    sfactor = GL_ONE_MINUS_SRC_ALPHA; break;
                    case BLEND_DEST_ALPHA:       sfactor = GL_DST_ALPHA; break;
                    case BLEND_INV_DEST_ALPHA:   sfactor = GL_ONE_MINUS_DST_ALPHA; break;
                    case BLEND_DEST_COLOR:       sfactor = GL_DST_COLOR; break;
                    case BLEND_INV_DEST_COLOR:   sfactor = GL_ONE_MINUS_DST_COLOR; break;
                    case BLEND_SRC_ALPHA_SAT:    sfactor = GL_SRC_ALPHA_SATURATE; break;
                }

                switch( dest ) {
                    case BLEND_ZERO:             dfactor = GL_ZERO; break;
                    case BLEND_ONE:              dfactor = GL_ONE; break;
                    case BLEND_SRC_COLOR:        dfactor = GL_SRC_COLOR; break;
                    case BLEND_INV_SRC_COLOR:    dfactor = GL_ONE_MINUS_SRC_COLOR; break;
                    case BLEND_SRC_ALPHA:        dfactor = GL_SRC_ALPHA; break;
                    case BLEND_INV_SRC_ALPHA:    dfactor = GL_ONE_MINUS_SRC_ALPHA; break;
                    case BLEND_DEST_ALPHA:       dfactor = GL_DST_ALPHA; break;
                    case BLEND_INV_DEST_ALPHA:   dfactor = GL_ONE_MINUS_DST_ALPHA; break;
                    case BLEND_DEST_COLOR:       dfactor = GL_DST_COLOR; break;
                    case BLEND_INV_DEST_COLOR:   dfactor = GL_ONE_MINUS_DST_COLOR; break;
                    case BLEND_SRC_ALPHA_SAT:    dfactor = GL_SRC_ALPHA_SATURATE; break;
                }

                glBlendFunc(sfactor, dfactor);
            }

            Mojo::Texture CreateTextureFromFile( const char* path, bool mipmap )
            {
                // todo: have this go through MOJO_GET_SERVICE(Filesystem)

                FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path, 0);
                if( !format ) return Mojo::Texture::invalid;
    
                FIBITMAP* dib = FreeImage_Load(format, path);
                if( !dib ) return Mojo::Texture::invalid;

                FIBITMAP* dib32 = FreeImage_ConvertTo32Bits(dib);
                if( !dib32 ) {
                    FreeImage_Unload(dib);
                    return Mojo::Texture::invalid;
                }

                FreeImage_Unload(dib);

                Mojo::Providers::Graphics::Texture texture;
                texture.type     = Mojo::Providers::Graphics::Texture::TEXUTRE_2D;
                texture.num_refs = 1;
                texture.width    = FreeImage_GetWidth(dib32);
                texture.height   = FreeImage_GetHeight(dib32);
                texture.depth    = 1;

                uint8_t* converted = new uint8_t[texture.width * texture.height * 4];
                uint8_t* pixels    = (unsigned char*)FreeImage_GetBits(dib32);

                for( uint32_t i = 0; i < texture.width * texture.height; ++i ) {
                    converted[i * 4 + 0] = pixels[i * 4 + 2];
                    converted[i * 4 + 1] = pixels[i * 4 + 1];
                    converted[i * 4 + 2] = pixels[i * 4 + 0];
                    converted[i * 4 + 3] = pixels[i * 4 + 3];
                }

                glGenTextures(1, (GLuint*)&texture.id);
                glBindTexture(GL_TEXTURE_2D, texture.id);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mipmap ? GL_LINEAR : GL_NEAREST);
                glTexImage2D(GL_TEXTURE_2D, 0, 4, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, converted);

                FreeImage_Unload(dib32);
                delete[] converted;

                if( mipmap ) {
                    glEnable(GL_TEXTURE_2D);
                    glGenerateMipmap(GL_TEXTURE_2D);
                }

                const uint32_t id = _next_texture_id++;
                _textures.insert(std::make_pair(id, texture));
                return Mojo::Texture(Mojo::Graphics::Handle::TEXTURE, id);
            }

            void GetTextureDimensions( const Mojo::Texture& texture_handle, uint32_t& width, uint32_t& height, uint32_t& depth )
            {
                if( !texture_handle.valid ) { width = 0; height = 0; depth = 0; return; }
                std::map<uint32_t, Mojo::Providers::Graphics::Texture>::const_iterator iter = _textures.find(texture_handle.id);
                if( iter == _textures.end() ) { width = 0; height = 0; depth = 0; return; }
                width = iter->second.width; height = iter->second.height; depth = iter->second.depth;
            }

            void SetTexture( const Mojo::Texture& texture_handle )
            {
                // todo: bind cache

                if( !texture_handle.valid ) { 
                    glDisable(GL_TEXTURE_2D);
                    return;
                }
                
                std::map<uint32_t, Mojo::Providers::Graphics::Texture>::const_iterator iter = _textures.find(texture_handle.id);
                if( iter == _textures.end() ) return;
                
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, iter->second.id);
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
                if( !handle.valid ) return;
                if( handle.type == Mojo::Graphics::Handle::TEXTURE ) {
                    std::map<uint32_t, Mojo::Providers::Graphics::Texture>::iterator iter = _textures.find(handle.id);
                    if( iter == _textures.end() ) return;
                    iter->second.num_refs++;
                }
            }

            void Dereference( const Mojo::Graphics::Handle& handle )
            {
                if( !handle.valid ) return;
                if( handle.type == Mojo::Graphics::Handle::TEXTURE ) {
                    std::map<uint32_t, Mojo::Providers::Graphics::Texture>::iterator iter = _textures.find(handle.id);
                    if( iter == _textures.end() ) return;
                    iter->second.num_refs--;
                    if( iter->second.num_refs != 0 ) return;
                    glDeleteTextures(1, &iter->second.id);
                    _textures.erase(iter);
                }
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

            Mojo::MessageQueue _input_messages;

            uint32_t _num_window_closed_callbacks;
            Mojo::Graphics::WindowClosedCallback _window_closed_callbacks[max_num_callbacks];

            uint32_t _num_window_resized_callbacks;
            Mojo::Graphics::WindowResizedCallback _window_resized_callbacks[max_num_callbacks];

            Mojo::Matrix4f _model_matrix, _view_matrix, _projection_matrix;

        private:
            struct Resource {
                uint32_t num_refs;
            };

            struct Texture : public Resource {
                enum Type {
                    TEXTURE_1D       = 1,
                    TEXTURE_1D_ARRAY = 2,
                    TEXUTRE_2D       = 3,
                };

                Type type;
                uint32_t width, height, depth;
                GLuint id;
            };

            uint32_t _next_texture_id;
            std::map<uint32_t, Texture> _textures;
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