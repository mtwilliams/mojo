#include <Mojo/Mojo.hpp>
#include <Mojo/Debug.hpp>
#include <Mojo/States/DefaultState.hpp>

#include <stdlib.h>
#include <string.h>

static void OnWindowClosed()
{
    exit(EXIT_SUCCESS);
}

int main( int argc, char** argv )
{
    Mojo::Graphics::Settings settings;
    settings.title       = "mojo";
    settings.width       = 800;
    settings.height      = 600;
    settings.num_samples = 0;
    settings.vsync       = false;
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
    Mojo::Services::Graphics* graphics_service = MOJO_GET_SERVICE(Graphics);

    if( !graphics_service->Create(settings) ) {
        Mojo::DebugPrintf(Mojo::DBG_CATASTROPHIC, "unable to create graphics context\n");
        return EXIT_FAILURE;
    }

    // Register callbacks
    MOJO_GRAPHICS_REGISTER_CALLBACK(OnWindowClosed, Mojo::Graphics::WindowClosedCallback::FromFunction<OnWindowClosed>());

    // Push the default state
    Mojo::States::Push(new Mojo::States::Default());

    while( true )
    {
        Mojo::State* state = Mojo::States::GetCurrentState();

        state->Update(1.0f);
        state->Draw();
        
        graphics_service->SwapBuffers();
    }

    return EXIT_SUCCESS;
}