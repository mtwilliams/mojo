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
    enum ClearTarget {
        CLEAR_COLOR   = (1 << 0),
        CLEAR_DEPTH   = (1 << 1),
        CLEAR_STENCIL = (1 << 2),
    };

    enum VertexFormat {
        VT_V2F             = 1,
        VT_V3F             = 2,
        VT_C4UB_V2F        = 3,
        VT_C4UB_V3F        = 4,
        VT_C3F_V3F         = 5,
        VT_N3F_V3F         = 6,
        VT_C4F_N3F_V3F     = 7,
        VT_T2F_V3F         = 8,
        VT_T4F_V4F         = 9,
        VT_T2F_C4UB_V3F    = 10,
        VT_T2F_C3F_V3F     = 11,
        VT_T2F_N3F_V3F     = 12,
        VT_T2F_C4F_N3F_V3F = 13,
        VT_T4F_C4F_N3F_V4F = 14,
    };

    enum ArrayType {
        VERTEX_ARRAY    = 1,
        INDEX_ARRAY     = 2,
        COLOR_ARRAY     = 3,
        TEX_COORD_ARRAY = 4,
    };

    enum PrimitiveTopology {
        PRIMITIVE_TOPOLOGY_UNDEFINED     = 0,
        PRIMITIVE_TOPOLOGY_POINTLIST     = 1,
        PRIMITIVE_TOPOLOGY_LINELIST      = 2,
        PRIMITIVE_TOPOLOGY_LINESTRIP     = 3,
        PRIMITIVE_TOPOLOGY_TRIANGLELIST  = 4,
        PRIMITIVE_TOPOLOGY_TRIANGLESTRIP = 5,
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
            
            virtual void Clear( uint32_t clear_targets, float r, float g, float b, float a, float depth = 1.0f, uint32_t stencil = 0, uint32_t buffer = 0 ) = 0;
            virtual void SwapBuffers() = 0;

            virtual void SetMatrix( const Mojo::Graphics::MatrixType matrix_type, const Mojo::Matrix4f& matrix ) = 0;

            virtual void Enable( const Mojo::Graphics::ArrayType array_type ) = 0;
            virtual void Disable( const Mojo::Graphics::ArrayType array_type ) = 0;

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