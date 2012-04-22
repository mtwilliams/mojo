#include <Mojo/Batch.hpp>

namespace Mojo
{
    Batch::Batch( Mojo::Graphics::VertexFormat vertex_format, size_t size )
        : _vertex_format(vertex_format)
        , _size(size)
        , _buffer(new uint8_t[size])
        , _num_vertices(0)
    {
    }

    Batch::~Batch()
    {
        delete[] _buffer;
    }

    struct Vertex {
        float s, t;
        uint8_t r, g, b, a;
        float x, y, z;
    };

    void Batch::Add( size_t num_vertices, const void* vertices )
    {
        mojo_assertf(_num_vertices + num_vertices <= GetMaxNumVertices(), "Vertex overflow.\n");
        const size_t vert_size = Mojo::Graphics::GetVertexFormatSize(_vertex_format);
        memcpy((void*)&_buffer[_num_vertices * vert_size], (void*)vertices, num_vertices * vert_size);     
        _num_vertices += num_vertices;
    }

    void Batch::Clear()
    {
        _num_vertices = 0;
    }
}