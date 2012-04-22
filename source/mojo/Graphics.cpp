#include <Mojo/Graphics.hpp>

#include <Mojo/Services.hpp>

namespace Mojo
{
namespace Graphics
{
    Handle::Handle( const Mojo::Graphics::Handle& other )
        : valid(other.valid)
        , type(other.type)
        , id(other.id)
    {
        Mojo::Services::Get<Mojo::Services::Graphics>()->Reference(*this);
    }

    Handle::Handle( unsigned type, unsigned id, unsigned valid )
        : valid(valid)
        , type(type)
        , id(id)
    {
        Mojo::Services::Get<Mojo::Services::Graphics>()->Reference(*this);
    }

    Handle::~Handle()
    {
        Mojo::Services::Get<Mojo::Services::Graphics>()->Dereference(*this);
    }

    Handle Handle::invalid = Handle(0, 0, 0);

    size_t GetVertexFormatSize( const Mojo::Graphics::VertexFormat vertex_format )
    {
        static const size_t lut[] = {
            8, 12, 12, 16, 24, 24, 40, 20, 32, 24, 32, 32, 48, 60
        };

        return lut[vertex_format - 1];
    }
}
}