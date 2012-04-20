#ifndef MOJO_CORE_ENVIRONMENT_HPP
#define MOJO_CORE_ENVIRONMENT_HPP

// Windows: 
#if defined(_WIN32)
    #define MOJO_WIN32_BUILD
#endif

#if defined(_WIN64)
    #define MOJO_WIN64_BUILD
#endif

#if defined(MOJO_WIN32_BUILD) || defined(MOJO_WIN64_BUILD)
    #define MOJO_WINDOWS_BUILD
#endif

// Linux:
#ifdef __linux__
    #define MOJO_LINUX_BUILD
#endif

// Mac OSX:
#if defined(__APPLE__) && defined(__MACH__)
    #define MOJO_MACOSX_BUILD
#endif

#endif /* MOJO_CORE_ENVIRONMENT_HPP */