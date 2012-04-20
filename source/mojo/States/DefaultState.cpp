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
        //Mojo::DebugPrintf(DBG_WARNING, "Default::Update\n");
    }

    void Default::Draw()
    {
        //Mojo::DebugPrintf(DBG_WARNING, "Default::Draw\n");

        static Mojo::Services::Graphics* graphics_service = MOJO_GET_SERVICE(Graphics);
        graphics_service->Clear(Mojo::Graphics::CLEAR_COLOR | Mojo::Graphics::CLEAR_DEPTH, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f);

        static const Mojo::Matrix4f model_matrix      = Mojo::Matrix4f::identity;
        static const Mojo::Matrix4f view_matrix       = Mojo::Matrix4f::identity;
        static const Mojo::Matrix4f projection_matrix = Mojo::Matrix4f::Ortho(0.0f, graphics_service->Width(), 0.0f, graphics_service->Height(), -1.0f, 1.0f);

        graphics_service->SetMatrix(Mojo::Graphics::MATRIX_MODEL, model_matrix);
        graphics_service->SetMatrix(Mojo::Graphics::MATRIX_VIEW, view_matrix);
        graphics_service->SetMatrix(Mojo::Graphics::MATRIX_PROJECTION, projection_matrix);

        struct Vertex {
            uint8_t r, g, b, a;
            float x, y, z;
        };

        static const Vertex vertices[] = {
            { 255, 0, 0, 255, graphics_service->Width(), 0.0f, 0.0f }, // top right
            { 0, 255, 0, 255, graphics_service->Width(), graphics_service->Height(), 0.0f }, // bottom right
            { 0, 0, 255, 255, 0.0f, graphics_service->Height(), 0.0f }  // bottom left
        };

        
        graphics_service->Enable(Mojo::Graphics::VERTEX_ARRAY);
        graphics_service->Enable(Mojo::Graphics::COLOR_ARRAY);
        graphics_service->SetInterleavedArrays(Mojo::Graphics::VT_C4UB_V3F, 0, (void*)&vertices[0]);
        graphics_service->Draw(Mojo::Graphics::PRIMITIVE_TOPOLOGY_TRIANGLELIST, 0, 3);
    }
}
}