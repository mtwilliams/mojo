#include <Mojo/Mojo.hpp>
#include <Mojo/Debug.hpp>
#include <Mojo/States/DefaultState.hpp>

#include <stdlib.h>
#include <string.h>

static void OnExit()
{
    MOJO_GET_SERVICE(Graphics)->Destroy();
}

static void OnWindowClosed()
{
    exit(EXIT_SUCCESS);
}

static void OnKeyPressed( Mojo::Input::Key key )
{
    using namespace Mojo::Input;
    if( key == KEY_ESC ) {
        exit(EXIT_SUCCESS);
    }
}

int main( int argc, char** argv )
{
    Mojo::Graphics::Settings settings;
    settings.title       = "mojo";
    settings.width       = 800;
    settings.height      = 600;
    settings.num_samples = 0;
    settings.vsync       = true;
    settings.fullscreen  = false;
    settings.no_resize   = true;

    // Parse command line arguments
    for( uint32_t i = 1; i < argc; ++i ) {
        if( sscanf(argv[i], "-w%u", &settings.width) >= 1 ) continue;
        if( sscanf(argv[i], "-h%u", &settings.height) >= 1 ) continue;
        if( sscanf(argv[i], "-s%u", &settings.num_samples) >= 1 ) continue;
        if( strncmp("-vsync", argv[i], 6) == 0 ) settings.vsync = true; continue;
        if( strncmp("-fullscreen", argv[i], 11) == 0 ) settings.fullscreen = true; continue;
        Mojo::DebugPrintf(Mojo::DBG_WARNING, "unknown argument: %s\n", argv[i]);
    }

    // Create graphics context
    Mojo::Services::Graphics* graphics = MOJO_GET_SERVICE(Graphics);

    if( !graphics->Create(settings) ) {
        Mojo::DebugPrintf(Mojo::DBG_CATASTROPHIC, "unable to create graphics context\n");
        return EXIT_FAILURE;
    }

    // Register callbacks
    MOJO_GRAPHICS_REGISTER_CALLBACK(OnWindowClosed, Mojo::Graphics::WindowClosedCallback::FromFunction<OnWindowClosed>());
    MOJO_INPUT_REGISTER_CALLBACK(OnKeyPressed, Mojo::Input::KeyPressedCallback::FromFunction<OnKeyPressed>());

    // Push the default state
    Mojo::States::Push(new Mojo::States::Default());

    // Register exit handler
    atexit(&OnExit);

    
    Mojo::HighResolutionClock::TimePoint last_time    = Mojo::HighResolutionClock::Now();
    Mojo::HighResolutionClock::TimePoint current_time = Mojo::HighResolutionClock::Now();

    while( true )
    {
        Mojo::HighResolutionClock::Duration time_diff = current_time - last_time;
        Mojo::Timestep timestep = time_diff.Miliseconds() / 1000.0f;

        Mojo::State* state = Mojo::States::GetCurrentState();
        state->Update(timestep);
        state->Draw();
        graphics->SwapBuffers();

        last_time    = current_time;
        current_time = Mojo::HighResolutionClock::Now();
    }

    return EXIT_SUCCESS;
}