#include <Mojo/Graphics.hpp>

#include <Mojo/Services.hpp>

namespace Mojo
{
namespace Graphics
{
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
}
}