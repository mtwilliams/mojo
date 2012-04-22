#ifndef MOJO_CHRONO_HPP
#define MOJO_CHRONO_HPP

#include <Mojo/Core.hpp>

namespace Mojo
{
    template <typename T = int32_t, uint32_t S = 1000>
    class Duration
    {
        public:
            Duration()
                : _ticks()
            {
            }

            Duration( const T& ticks )
                : _ticks(ticks)
            {
            }

            Duration( const Mojo::Duration<T>& other )
                : _ticks(other._ticks)
            {
            }

            inline Mojo::Duration<T, S> operator+( const Mojo::Duration<T, S>& other ) const { return Mojo::Duration<T, S>(_ticks + other._ticks); }
            inline Mojo::Duration<T, S> operator-( const Mojo::Duration<T, S>& other ) const { return Mojo::Duration<T, S>(_ticks - other._ticks); }
            inline Mojo::Duration<T, S>& operator+=( const Mojo::Duration<T, S>& other ) { ticks += other._ticks; return *this; }
            inline Mojo::Duration<T, S>& operator-=( const Mojo::Duration<T, S>& other ) { ticks -= other._ticks; return *this; }

            inline bool operator==( const Mojo::Duration<T, S>& other ) const { return ticks == other._ticks; }
            inline bool operator!=( const Mojo::Duration<T, S>& other ) const { return ticks != other._ticks; }
            inline bool operator>(  const Mojo::Duration<T, S>& other ) const { return ticks > other._ticks; }
            inline bool operator<(  const Mojo::Duration<T, S>& other ) const { return ticks < other._ticks; }
            inline bool operator>=( const Mojo::Duration<T, S>& other ) const { return ticks >= other._ticks; }
            inline bool operator<=( const Mojo::Duration<T, S>& other ) const { return ticks <= other._ticks; }

            T Seconds() const     { return _ticks / S; };
            T Miliseconds() const { return _ticks / (S / 1000); };
            T Nanoseconds() const { return _ticks / (S / 1000000000); };

        private:
            T _ticks;
    };

    template <typename C, typename D = Mojo::Duration<>>
    class TimePoint
    {
        public:
            TimePoint()
                : _duration()
            {
            }

            TimePoint( const D& duration )
                : _duration(duration)
            {
            }

            inline D operator+( const Mojo::TimePoint<C, D>& other ) const { return _duration + other._duration; }
            inline D operator-( const Mojo::TimePoint<C, D>& other ) const { return _duration - other._duration; }

            inline bool operator==( const Mojo::TimePoint<C, D>& other ) const { return _duration == other._duration; }
            inline bool operator!=( const Mojo::TimePoint<C, D>& other ) const { return _duration != other._duration; }
            inline bool operator>(  const Mojo::TimePoint<C, D>& other ) const { return _duration >  other._duration; }
            inline bool operator<(  const Mojo::TimePoint<C, D>& other ) const { return _duration <  other._duration; }
            inline bool operator>=( const Mojo::TimePoint<C, D>& other ) const { return _duration >= other._duration; }
            inline bool operator<=( const Mojo::TimePoint<C, D>& other ) const { return _duration <= other._duration; }

        private:
            D _duration;
    };

    class SystemClock
    {
        public:
            typedef Mojo::Duration<> Duration;
            typedef Mojo::TimePoint<Mojo::SystemClock, SystemClock::Duration> TimePoint;

        public:
            static bool IsSteady();
            static Mojo::SystemClock::TimePoint Now();
    };

    class SteadyClock
    {
        public:
            typedef Mojo::Duration<> Duration;
            typedef Mojo::TimePoint<Mojo::SteadyClock, SteadyClock::Duration> TimePoint;

        public:
            static bool IsSteady();
            static Mojo::SteadyClock::TimePoint Now();
    };

    class HighResolutionClock
    {
        public:
            typedef Mojo::Duration<uint64_t, 1000000> Duration;
            typedef Mojo::TimePoint<Mojo::HighResolutionClock, HighResolutionClock::Duration> TimePoint;

        public:
            static bool IsSteady();
            static HighResolutionClock::TimePoint Now();
    };
}

#endif /* MOJO_CHRONO_HPP */