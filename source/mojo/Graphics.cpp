#include <Mojo/Graphics.hpp>

#include <Mojo/Services.hpp>

namespace Mojo
{
namespace Graphics
{
    Handle::Handle( unsigned type, unsigned id )
        : type(type)
        , id(id)
    {
        Mojo::Services::Get<Mojo::Services::Graphics>()->Reference(*this);
    }

    Handle::~Handle()
    {
        Mojo::Services::Get<Mojo::Services::Graphics>()->Dereference(*this);
    }
}
}