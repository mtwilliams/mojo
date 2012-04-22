#include <Mojo/SpriteBatch.hpp>
#include <Mojo/Services.hpp>

namespace Mojo
{
    SpriteBatch::SpriteBatch( size_t num_sprites )
        : Mojo::Batch(Mojo::Graphics::VT_T2F_C4UB_V3F, Mojo::Graphics::GetVertexFormatSize(Mojo::Graphics::VT_T2F_C4UB_V3F) * num_sprites * 6)
        , _in_batch(false)
        , _sprite_sheet(Mojo::Texture::invalid)
        , _sprite_sheet_width(0)
        , _sprite_sheet_height(0)
    {
    }

    SpriteBatch::~SpriteBatch()
    {
    }

    void SpriteBatch::Begin( const Mojo::Texture& sprite_sheet )
    {
        mojo_assertf(!_in_batch, "SpriteBatch::Begin without SpriteBatch::End\n");
        uint32_t unused;
        MOJO_GET_SERVICE(Graphics)->GetTextureDimensions(sprite_sheet, _sprite_sheet_width, _sprite_sheet_height, unused);
        _in_batch = true; _sprite_sheet = sprite_sheet;
    }

    struct Vertex {
        float s, t;
        uint8_t r, g, b, a;
        float x, y, z;
    };

    void SpriteBatch::End()
    {
        mojo_assertf(_in_batch, "SpriteBatch::End without SpriteBatch::Begin\n");

        Mojo::Services::Graphics* graphics_service = MOJO_GET_SERVICE(Graphics);
        graphics_service->SetTexture(_sprite_sheet);
        graphics_service->Enable(Mojo::Graphics::VERTEX_ARRAY);
        graphics_service->Enable(Mojo::Graphics::COLOR_ARRAY);
        graphics_service->Enable(Mojo::Graphics::TEX_COORD_ARRAY);
        graphics_service->SetInterleavedArrays(Mojo::Graphics::VT_T2F_C4UB_V3F, 0, GetVertices());
        graphics_service->Draw(Mojo::Graphics::PRIMITIVE_TOPOLOGY_TRIANGLELIST, 0, GetNumVertices());
        Clear();
        
        _in_batch = false; _sprite_sheet = Mojo::Texture::invalid;
        _sprite_sheet_width = 0; _sprite_sheet_height = 0;
    }

    void SpriteBatch::Draw( const Mojo::Sprite& sprite, uint32_t frame, const Mojo::Vector3f position, const Mojo::Vector2f& scale, const Mojo::Color& color )
    {
        const uint32_t max_verts = GetMaxNumVertices();
        if( GetNumVertices() + 6 > max_verts ) return;

        const Mojo::Sprite::Frame sprite_frame = sprite.GetFrame(frame);
        
        const float tex_coords[4] = {
            (float)(sprite_frame.x) / _sprite_sheet_width,
            1.0f - (float)(sprite_frame.y) / _sprite_sheet_height,
            (float)(sprite_frame.x + sprite_frame.width) / _sprite_sheet_width,
            1.0f - (float)(sprite_frame.y + sprite_frame.height) / _sprite_sheet_height
        };

        Mojo::Matrix4f sprite_mat = Mojo::Matrix4f::identity;
        sprite_mat.Translate(position + Mojo::Vector2f(sprite_frame.width / 2 * -scale.x, sprite_frame.height / 2 * -scale.y));
        sprite_mat.Scale(scale);

        const Mojo::Vector3f positions[4] = {
            sprite_mat * Mojo::Vector3f(sprite_frame.x, sprite_frame.y + sprite_frame.height, 0.0f),
            sprite_mat * Mojo::Vector3f(sprite_frame.x, sprite_frame.y, 0.0f),
            sprite_mat * Mojo::Vector3f(sprite_frame.x + sprite_frame.width, sprite_frame.y, 0.0f),
            sprite_mat * Mojo::Vector3f(sprite_frame.x + sprite_frame.width, sprite_frame.y + sprite_frame.height, 0.0f)
        };

        Vertex vertices[6] = {
            { tex_coords[0], tex_coords[3], color.r, color.g, color.b, color.a, positions[0].x, positions[0].y, positions[0].z },
            { tex_coords[0], tex_coords[1], color.r, color.g, color.b, color.a, positions[1].x, positions[1].y, positions[1].z },
            { tex_coords[2], tex_coords[1], color.r, color.g, color.b, color.a, positions[2].x, positions[2].y, positions[2].z },
            { tex_coords[2], tex_coords[1], color.r, color.g, color.b, color.a, positions[2].x, positions[2].y, positions[2].z },
            { tex_coords[2], tex_coords[3], color.r, color.g, color.b, color.a, positions[3].x, positions[3].y, positions[3].z },
            { tex_coords[0], tex_coords[3], color.r, color.g, color.b, color.a, positions[0].x, positions[0].y, positions[0].z }
        };

        Add(6, (const void*)&vertices[0]);
    }
}