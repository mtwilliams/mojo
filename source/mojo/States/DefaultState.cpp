#include <Mojo/States/DefaultState.hpp>

#include <Mojo/Debug.hpp>
#include <Mojo/Services.hpp>

namespace Mojo
{
namespace States
{
    Default::Default()
        : _cube_wireframe(MOJO_GET_SERVICE(Graphics)->CreateTextureFromFile("data/textures/cube_wireframe.png", true))
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
        graphics_service->Clear(Mojo::Graphics::CLEAR_COLOR | Mojo::Graphics::CLEAR_DEPTH, 0.0f, 0.5f, 1.0f, 1.0f, 1.0f);

        static const Mojo::Matrix4f model_matrix      = Mojo::Matrix4f::identity;
        static const Mojo::Matrix4f view_matrix       = Mojo::Matrix4f::identity;
        static const Mojo::Matrix4f projection_matrix = Mojo::Matrix4f::Ortho(0.0f, graphics_service->Width(), 0.0f, graphics_service->Height(), -1.0f, 1.0f);

        graphics_service->SetMatrix(Mojo::Graphics::MATRIX_MODEL, model_matrix);
        graphics_service->SetMatrix(Mojo::Graphics::MATRIX_VIEW, view_matrix);
        graphics_service->SetMatrix(Mojo::Graphics::MATRIX_PROJECTION, projection_matrix);

        struct Vertex {
            float s, t;
            uint8_t r, g, b, a;
            float x, y, z;
        };

        static const Vertex vertices[] = {
            { 1.0f, 1.0f, 255, 255, 255, 128, graphics_service->Width(), graphics_service->Height() / 2, 0.5f }, // top right
            { 1.0f, 0.0f, 255, 255, 255, 128, graphics_service->Width(), graphics_service->Height(), 0.5f }, // bottom right
            { 0.0f, 0.0f, 255, 255, 255, 128, graphics_service->Width() / 2, graphics_service->Height(), 0.5f }, // bottom left

            { 1.0f, 1.0f, 255, 0, 0, 128, graphics_service->Width(), 0.0f, 0.0f },                       // top right
            { 1.0f, 0.0f, 0, 255, 0, 128, graphics_service->Width(), graphics_service->Height(), 0.0f }, // bottom right
            { 0.0f, 0.0f, 0, 0, 255, 128, 0.0f, graphics_service->Height(), 0.0f },                      // bottom left
        };

        graphics_service->SetTexture(_cube_wireframe);
        graphics_service->SetBlendFunc(Mojo::Graphics::BLEND_SRC_ALPHA, Mojo::Graphics::BLEND_INV_SRC_ALPHA);
        graphics_service->Enable(Mojo::Graphics::VERTEX_ARRAY);
        graphics_service->Enable(Mojo::Graphics::COLOR_ARRAY);
        graphics_service->Enable(Mojo::Graphics::TEX_COORD_ARRAY);
        graphics_service->SetInterleavedArrays(Mojo::Graphics::VT_T2F_C4UB_V3F, 0, (void*)&vertices[0]);
        graphics_service->Draw(Mojo::Graphics::PRIMITIVE_TOPOLOGY_TRIANGLELIST, 0, 6);
    }
}
}