#include <Mojo/TextBatch.hpp>
#include <Mojo/Services.hpp>

namespace Mojo
{
    TextBatch::TextBatch( size_t num_characters )
        : Mojo::Batch(Mojo::Graphics::VT_T2F_C4UB_V3F, Mojo::Graphics::GetVertexFormatSize(Mojo::Graphics::VT_T2F_C4UB_V3F) * num_characters * 6)
        , _in_batch(false)
        , _font(NULL)
    {
    }

    TextBatch::~TextBatch()
    {
    }

    void TextBatch::Begin( const Mojo::Font& font )
    {
        mojo_assertf(!_in_batch, "TextBatch::Begin without TextBatch::End\n");
        _in_batch = true; _font = &font;
    }

    void TextBatch::End()
    {
        mojo_assertf(_in_batch, "TextBatch::End without TextBatch::Begin\n");

        Mojo::Services::Graphics* graphics = MOJO_GET_SERVICE(Graphics);
        graphics->SetTexture(_font->_font_atlas);
        graphics->Enable(Mojo::Graphics::VERTEX_ARRAY);
        graphics->Enable(Mojo::Graphics::COLOR_ARRAY);
        graphics->Enable(Mojo::Graphics::TEX_COORD_ARRAY);
        graphics->SetInterleavedArrays(Mojo::Graphics::VT_T2F_C4UB_V3F, 0, GetVertices());
        graphics->Draw(Mojo::Graphics::PRIMITIVE_TOPOLOGY_TRIANGLELIST, 0, GetNumVertices());
        Clear();
        
        _in_batch = false; _font = NULL;
    }

    struct Vertex {
        float s, t;
        uint8_t r, g, b, a;
        float x, y, z;
    };

    void TextBatch::Draw( const char* text, const Mojo::Vector3f position, const Mojo::Color& color )
    {
        uint32_t num_visible_chars = 0; {
            const char* titer = text;
            while( const char ch = *titer++ ) { switch( ch ) { 
                case ' ': case '\t': case '\n': case '\r': break;
                default: ++num_visible_chars; break;
            }}
        }

        const uint32_t max_verts = GetMaxNumVertices();
        if( GetNumVertices() + num_visible_chars * 6 > max_verts ) return;

        float x_offset = 0.0f, y_offset = 0.0f;

        const char* titer = text;
        while( const char ch = *titer++ ) {
            switch( ch ) {
                case ' ':  x_offset += _font->GetGlyphOffset(' '); break;
                case '\t': x_offset += _font->GetGlyphOffset(' ') * 4.0f; break;
                case '\n': x_offset = 0.0f; y_offset += _font->GetLineHeight(); break;
                case '\r': break;
                default: {


                    x_offset += _font->GetGlyphOffset(ch); break;
                } break;
            }
        }
    }
}