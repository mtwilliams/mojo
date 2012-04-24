#ifndef MOJO_SERVICES_GRAPHICS_HPP
#define MOJO_SERVICES_GRAPHICS_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Math.hpp>
#include <Mojo/Graphics.hpp>

#define MOJO_GRAPHICS_REGISTER_CALLBACK( event, callback ) Mojo::Services::Get<Mojo::Services::Graphics>()->Register_##event(callback);
#define MOJO_GRAPHICS_DEREGISTER_CALLBACK( event, id ) Mojo::Services::Get<Mojo::Services::Graphics>()->Deregister_##event(id);

namespace Mojo
{
namespace Graphics
{
    enum ArrayType {
        VERTEX_ARRAY    = 1,
        INDEX_ARRAY     = 2,
        COLOR_ARRAY     = 3,
        TEX_COORD_ARRAY = 4,
    };

    enum MatrixType {
        MATRIX_MODEL      = 1,
        MATRIX_VIEW       = 2,
        MATRIX_PROJECTION = 3,
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

            virtual uint32_t Width() = 0;
            virtual uint32_t Height() = 0;
            
            virtual void Clear( uint32_t clear_targets, const Mojo::Color& color, float depth = 1.0f, uint32_t stencil = 0, uint32_t buffer = 0 ) = 0;
            virtual void SwapBuffers() = 0;

            virtual void SetMatrix( const Mojo::Graphics::MatrixType matrix_type, const Mojo::Matrix4f& matrix ) = 0;

            virtual void Enable( const Mojo::Graphics::State state ) = 0;
            virtual void Disable( const Mojo::Graphics::State state ) = 0;

            virtual void Enable( const Mojo::Graphics::ArrayType array_type ) = 0;
            virtual void Disable( const Mojo::Graphics::ArrayType array_type ) = 0;

            virtual void SetBlendOp( const Mojo::Graphics::BlendOp blend_op ) = 0;
            virtual void SetBlendFunc( const Mojo::Graphics::BlendFunc src, const Mojo::Graphics::BlendFunc dest ) = 0;

            virtual Mojo::Texture CreateTexture2D( const uint32_t width, const uint32_t height, const Mojo::Graphics::TextureFormat tex_format, const void* pixels, const bool mipmap = true ) = 0;
            virtual Mojo::Texture CreateTextureFromFile( const char* path, bool mipmap = true ) = 0;
            virtual void GetTextureDimensions( const Mojo::Texture& texture_handle, uint32_t& width, uint32_t& height, uint32_t& depth ) = 0;
            virtual void SetTexture( const Mojo::Texture& texture_handle ) = 0;

            virtual void SetInterleavedArrays( const Mojo::Graphics::VertexFormat vertex_format, size_t stride, const void* data ) = 0;
            virtual void Draw( const Mojo::Graphics::PrimitiveTopology prim_topology, uint32_t first, size_t count ) = 0;

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