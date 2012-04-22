#include <Mojo/States/DefaultState.hpp>

#include <Mojo/Sprite.hpp>
#include <Mojo/SpriteBatch.hpp>

#include <Mojo/Debug.hpp>
#include <Mojo/Services.hpp>

namespace Mojo
{
namespace States
{
    static float cucco_rot = 0.0f;
    static float cucco_rot_speed = 36.0f;
    static float cucco_radius = 128;
    static Mojo::Vector2f cucco_pos = Mojo::Vector2f(400, 300);

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

        cucco_rot += cucco_rot_speed * timestep;
        if( cucco_rot >= 360.0f ) cucco_rot -= 360.0f;

        const float r_cucco_rot = Mojo::DegressToRadians(cucco_rot);

        cucco_pos = Mojo::Vector2f(400.0f + cos(r_cucco_rot) * cucco_radius, 300.0f + sin(r_cucco_rot) * cucco_radius);
    }

    void Default::Draw()
    {
        //Mojo::DebugPrintf(DBG_WARNING, "Default::Draw\n");

        static Mojo::Services::Graphics* graphics_service = MOJO_GET_SERVICE(Graphics);
        graphics_service->Clear(Mojo::Graphics::CLEAR_COLOR | Mojo::Graphics::CLEAR_DEPTH, Mojo::Colors::Gray, 1.0f);

        static const Mojo::Matrix4f model_matrix      = Mojo::Matrix4f::identity;
        static const Mojo::Matrix4f view_matrix       = Mojo::Matrix4f::identity;
        static const Mojo::Matrix4f projection_matrix = Mojo::Matrix4f::Ortho(0.0f, graphics_service->Width(), 0.0f, graphics_service->Height(), -1.0f, 1.0f);

        graphics_service->SetMatrix(Mojo::Graphics::MATRIX_MODEL, model_matrix);
        graphics_service->SetMatrix(Mojo::Graphics::MATRIX_VIEW, view_matrix);
        graphics_service->SetMatrix(Mojo::Graphics::MATRIX_PROJECTION, projection_matrix);

        static Mojo::Texture sprite_sheet = graphics_service->CreateTextureFromFile("data/textures/sheet.png", false);
        static const Mojo::Sprite::Frame cucco_frames[] = {
            { 0, 0, 16, 16 }
        };

        static Mojo::Sprite cucco = Mojo::Sprite(1, &cucco_frames[0]);
        static Mojo::SpriteBatch sprite_batch = Mojo::SpriteBatch(1);

        sprite_batch.Begin(sprite_sheet);
        sprite_batch.Draw(cucco, 0, cucco_pos, Mojo::Vector2f(4.0f, 4.0f));
        sprite_batch.End();
    }
}
}