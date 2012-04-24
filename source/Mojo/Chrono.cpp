#include <Mojo/Chrono.hpp>

#if defined(MOJO_WINDOWS_BUILD)
    #include <windows.h>
#elif defined(MOJO_LINUX_BUILD)
    #include <time.h>
#else
    #error Not supported.
#endif

namespace Mojo
{
    #if defined(MOJO_WINDOWS_BUILD)
        bool SystemClock::IsSteady()
        {
            return true;
        }

        Mojo::SystemClock::TimePoint SystemClock::Now()
        {
            return Mojo::SystemClock::TimePoint(Mojo::SystemClock::Duration(GetTickCount()));
        }

        bool SteadyClock::IsSteady()
        {
            return true;
        }

        Mojo::SteadyClock::TimePoint SteadyClock::Now()
        {
            return Mojo::SteadyClock::TimePoint(Mojo::SteadyClock::Duration(GetTickCount()));
        }

        bool HighResolutionClock::IsSteady()
        {
            return true;
        }

        HighResolutionClock::TimePoint HighResolutionClock::Now()
        {
            // FIXME: return miliseconds, not nano-seconds.

            // TODO: Compensate for performance counter leaps (see Q274323)
            // TODO: Take into account the pitfalls with QueryPerformanceCounter on multiple processors
            static LARGE_INTEGER frequency;
            static LARGE_INTEGER start_count;
            static bool use_high_freq = QueryPerformanceFrequency(&frequency) != 0;
            static bool have_start_count = QueryPerformanceCounter(&start_count) != 0;

            if( !use_high_freq || !have_start_count ) {
                goto low_freq;
            }

            LARGE_INTEGER current_count;
            if( !QueryPerformanceCounter(&current_count) ) {
                goto low_freq;
            }

            uint64_t miliseconds = (uint64_t)(1000 * (current_count.QuadPart - start_count.QuadPart) / frequency.QuadPart);
            return Mojo::HighResolutionClock::TimePoint(Mojo::HighResolutionClock::Duration(miliseconds));

            low_freq:
                return Mojo::HighResolutionClock::TimePoint(Mojo::HighResolutionClock::Duration((uint64_t)GetTickCount()));
        }
    #elif defined(MOJO_LINUX_BUILD)
        bool SystemClock::IsSteady()
        {
            return true;
        }

        Mojo::SystemClock::TimePoint SystemClock::Now()
        {
            timespec ts;
            clock_gettime(CLOCK_MONOTONIC, &ts);
            return Mojo::SystemClock::TimePoint(Mojo::SystemClock::Duration((int32_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000)));
        }

        bool SteadyClock::IsSteady()
        {
            return true;
        }

        Mojo::SteadyClock::TimePoint SteadyClock::Now()
        {
            timespec ts;
            clock_gettime(CLOCK_MONOTONIC, &ts);
            return Mojo::SteadyClock::TimePoint(Mojo::SteadyClock::Duration((int32_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000)));
        }

        bool HighResolutionClock::IsSteady()
        {
            // is it?
            return true;
        }

        HighResolutionClock::TimePoint HighResolutionClock::Now()
        {
            timespec ts;
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
            return Mojo::HighResolutionClock::TimePoint(Mojo::HighResolutionClock::Duration((uint64_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000)));
        }
    #endif
}