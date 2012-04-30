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
    static Mojo::Font font;

    Default::Default()
    {
        font.CreateFromFile("data/fonts/verdana_bold.ttf", 12, true);
    }

    Default::~Default()
    {
    }

    void Default::Update( const Mojo::Timestep timestep )
    {
    }

    void Default::Draw()
    {
        static Mojo::Services::Graphics* graphics = MOJO_GET_SERVICE(Graphics);
        graphics->Clear(Mojo::Graphics::CLEAR_COLOR | Mojo::Graphics::CLEAR_DEPTH, Mojo::Color(51, 51, 51), 1.0f);

        static const Mojo::Matrix4f model_matrix      = Mojo::Matrix4f::identity;
        static const Mojo::Matrix4f view_matrix       = Mojo::Matrix4f::identity;
        static const Mojo::Matrix4f projection_matrix = Mojo::Matrix4f::Ortho(0.0f, graphics->Width(), 0.0f, graphics->Height(), -1.0f, 1.0f);

        graphics->SetMatrix(Mojo::Graphics::MATRIX_MODEL, model_matrix);
        graphics->SetMatrix(Mojo::Graphics::MATRIX_VIEW, view_matrix);
        graphics->SetMatrix(Mojo::Graphics::MATRIX_PROJECTION, projection_matrix);

        const struct { uint8_t r, g, b, a; float x, y; } bg_quad[6] = {
            { 0xDE, 0xDE, 0xDE, 0xFF,  },
        };

        const char* text = "singleplayer\nmultiplayer\nsettings\nquit game";

        static Mojo::TextBatch text_batch = Mojo::TextBatch(256);
        static const Mojo::Recti text_bounds = font.Measure(text);
        static const Mojo::Vector2f text_pos = Mojo::Vector2f((int)((800.0f - text_bounds.width) / 2.0f), (int)((600.0f - text_bounds.height) / 2.0f));

        MOJO_GET_SERVICE(Graphics)->SetBlendFunc(Mojo::Graphics::BLEND_SRC_ALPHA, Mojo::Graphics::BLEND_INV_SRC_ALPHA);

        text_batch.Begin(font);
        text_batch.Draw(text, text_pos, Mojo::Color(0xFF, 0xFF, 0xFF));
        //text_batch.Draw(text, text_pos + Mojo::Vector2f(1.0f, 1.0f), Mojo::Colors::Black);
        text_batch.End();
    }
}
}