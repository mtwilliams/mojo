#include <Mojo/States/DefaultState.hpp>

#include <Mojo/Debug.hpp>
#include <Mojo/Services.hpp>

namespace Mojo
{
namespace States
{
    Default::Default()
    {
    }

    Default::~Default()
    {
    }

    void Default::Update( const Mojo::Timestep timestep )
    {
        Mojo::DebugPrintf(DBG_WARNING, "Default::Update\n");
    }

    void Default::Draw()
    {
        Mojo::DebugPrintf(DBG_WARNING, "Default::Draw\n");

        static Mojo::Services::Graphics* graphics_service = MOJO_GET_SERVICE(Graphics);
        graphics_service->Clear(Mojo::Graphics::CLEAR_COLOR | Mojo::Graphics::CLEAR_DEPTH, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f);
    }
}
}