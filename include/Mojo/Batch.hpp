#ifndef MOJO_BATCH_HPP
#define MOJO_BATCH_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Graphics.hpp>

namespace Mojo
{
    class MOJO_CLASS_EXPORT(Batch) : public Mojo::NonCopyable
    {
        public:
            Batch( Mojo::Graphics::VertexFormat vertex_format, size_t size );
            virtual ~Batch();

            void Add( size_t num_vertices, const void* vertices );
            void Clear();

            inline const Mojo::Graphics::VertexFormat GetVertexFormat() const { return _vertex_format; }
            inline const void* GetVertices() const { return (const void*)_buffer; }
            inline uint32_t GetNumVertices() const { return _num_vertices; }
            inline uint32_t GetMaxNumVertices() const { return _size / Mojo::Graphics::GetVertexFormatSize(_vertex_format); }

        private:
            const Mojo::Graphics::VertexFormat _vertex_format;
            const size_t _size;
            uint8_t* _buffer;
            uint32_t _num_vertices;
    };
}

#endif /* MOJO_BATCH_HPP */