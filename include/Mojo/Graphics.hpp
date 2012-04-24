#ifndef MOJO_GRAPHICS_HPP
#define MOJO_GRAPHICS_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Color.hpp>
#include <Mojo/Colors.hpp>

namespace Mojo
{
namespace Graphics
{
    enum ClearTarget {
        CLEAR_COLOR   = (1 << 0),
        CLEAR_DEPTH   = (1 << 1),
        CLEAR_STENCIL = (1 << 2),
    };

    enum State {
        BLEND      = 1,
        DEPTH_TEST = 2,
    };

    enum TextureFormat {
        TF_RGB8  = 1,
        TF_RGBA8 = 2,
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

    enum BlendOp {
        BLEND_OP_ADD          = 1,
        BLEND_OP_SUBTRACT     = 2,
        BLEND_OP_REV_SUBTRACT = 3,
        BLEND_OP_MIN          = 4,
        BLEND_OP_MAX          = 5,
    };

    enum BlendFunc {
        BLEND_ZERO             = 1,
        BLEND_ONE              = 2,
        BLEND_SRC_COLOR        = 3,
        BLEND_INV_SRC_COLOR    = 4,
        BLEND_SRC_ALPHA        = 5,
        BLEND_INV_SRC_ALPHA    = 6,
        BLEND_DEST_ALPHA       = 7,
        BLEND_INV_DEST_ALPHA   = 8,
        BLEND_DEST_COLOR       = 9,
        BLEND_INV_DEST_COLOR   = 10,
        BLEND_SRC_ALPHA_SAT    = 11,
    };

    enum PrimitiveTopology {
        PRIMITIVE_TOPOLOGY_UNDEFINED     = 0,
        PRIMITIVE_TOPOLOGY_POINTLIST     = 1,
        PRIMITIVE_TOPOLOGY_LINELIST      = 2,
        PRIMITIVE_TOPOLOGY_LINESTRIP     = 3,
        PRIMITIVE_TOPOLOGY_TRIANGLELIST  = 4,
        PRIMITIVE_TOPOLOGY_TRIANGLESTRIP = 5,
    };

    MOJO_EXPORT(size_t GetVertexFormatSize( const Mojo::Graphics::VertexFormat vertex_format ));

    struct MOJO_CLASS_EXPORT(Handle) {
        enum Type {
            TEXTURE       = 1,
            SHADER        = 2,
            RENDER_TARGET = 3,
        };

        unsigned valid : 1;
        unsigned type  : 3;
        unsigned id    : 12;

        Handle( const Mojo::Graphics::Handle& other );
        Handle( unsigned type, unsigned id, unsigned valid = 1 );
        ~Handle();

        static Handle invalid;
    };
}
    typedef Mojo::Graphics::Handle Texture, Shader, RenderTarget;
}

#endif /* MOJO_GRAPHICS_HPP */