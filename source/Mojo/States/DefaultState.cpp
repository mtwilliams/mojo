#include <Mojo/States/DefaultState.hpp>

#include <Mojo/Sprite.hpp>
#include <Mojo/SpriteBatch.hpp>

#include <Mojo/Font.hpp>
#include <Mojo/TextBatch.hpp>

#include <Mojo/Debug.hpp>
#include <Mojo/Services.hpp>

namespace Mojo
{
namespace States
{
    static float moon_rot = 0.0f;
    static float moon_rot_speed = 60.0f;
    static float moon_radius = 128;
    static Mojo::Vector2f moon_pos = Mojo::Vector2f(400, 300);
    static Mojo::Font freeroad;

    Default::Default()
        : _cube_wireframe(MOJO_GET_SERVICE(Graphics)->CreateTextureFromFile("data/textures/cube_wireframe.png", true))
    {
        freeroad.CreateFromFile("data/fonts/freeroad.ttf", 12);
    }

    Default::~Default()
    {
    }

    void Default::Update( const Mojo::Timestep timestep )
    {
        //Mojo::DebugPrintf(DBG_WARNING, "Default::Update\n");

        moon_rot += moon_rot_speed * timestep;
        if( moon_rot >= 360.0f ) moon_rot -= 360.0f;

        const float r_moon_rot = Mojo::DegressToRadians(moon_rot);

        moon_pos = Mojo::Vector2f(400.0f + cos(r_moon_rot) * moon_radius, 300.0f + sin(r_moon_rot) * moon_radius);
    }

    void Default::Draw()
    {
        //Mojo::DebugPrintf(DBG_WARNING, "Default::Draw\n");

        static Mojo::Services::Graphics* graphics = MOJO_GET_SERVICE(Graphics);
        graphics->Clear(Mojo::Graphics::CLEAR_COLOR | Mojo::Graphics::CLEAR_DEPTH, Mojo::Colors::Gray, 1.0f);

        static const Mojo::Matrix4f model_matrix      = Mojo::Matrix4f::identity;
        static const Mojo::Matrix4f view_matrix       = Mojo::Matrix4f::identity;
        static const Mojo::Matrix4f projection_matrix = Mojo::Matrix4f::Ortho(0.0f, graphics->Width(), 0.0f, graphics->Height(), -1.0f, 1.0f);

        graphics->SetMatrix(Mojo::Graphics::MATRIX_MODEL, model_matrix);
        graphics->SetMatrix(Mojo::Graphics::MATRIX_VIEW, view_matrix);
        graphics->SetMatrix(Mojo::Graphics::MATRIX_PROJECTION, projection_matrix);

        static Mojo::Texture sprite_sheet = graphics->CreateTextureFromFile("data/textures/sheet.png", false);
        static const Mojo::Sprite::Frame moon_frames[] = {
            { 0, 0, 16, 16 }
        };

        static const Mojo::Sprite::Frame sun_frames[] = {
            { 48, 16, 32, 32 }
        };

        static Mojo::Sprite moon = Mojo::Sprite(1, &moon_frames[0]);
        static Mojo::Sprite sun  = Mojo::Sprite(1, &sun_frames[0]);
        static Mojo::SpriteBatch sprite_batch = Mojo::SpriteBatch(2);

        sprite_batch.Begin(sprite_sheet);
        sprite_batch.Draw(sun,  0, Mojo::Vector2f(400.0f, 300.0f), Mojo::Vector2f(4.0f, 4.0f));
        sprite_batch.Draw(moon, 0, moon_pos, Mojo::Vector2f(4.0f, 4.0f));
        sprite_batch.End();

        static Mojo::TextBatch text_batch = Mojo::TextBatch(strlen("Hello, Mojo!"));
        text_batch.Begin(freeroad);
        text_batch.Draw("Hello, Mojo!", Mojo::Vector2f(1.0f, 1.0f), Mojo::Colors::Red);
        text_batch.End();
    }
}
}