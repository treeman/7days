#ifndef TIMER_HPP_INCLUDED
#define TIMER_HPP_INCLUDED

#include <SFML/System.hpp>

namespace Tree
{
    class Timer {
    public:
        Timer();
        virtual ~Timer();

        void Start(); // Will not restart, you can call in a loop!
        void Pause();
        void Stop();
        void Toggle(); // Will toggle start and pause

        void Restart(); // Stop and Start

        float GetTime() const;
        void SetTime( float time );

        void SetSpeed( float multiplier );
        float GetSpeed() const;

        bool IsStarted() const;
        bool IsPaused() const;
    private:
        virtual float GetTimeStep() const;
        virtual void UpdateTimeAcc();

        float start_tick;
        float pause_tick;
        float time;

        float speed;

        bool is_started;
        bool is_paused;

        sf::Clock clock;
    };

    class CountDown : public Timer {
    public:
        CountDown();
        CountDown( float limit );
        virtual ~CountDown();

        void SetLimit( float limit );
        float GetLimit() const;

        bool IsDone();
    private:
        float limit;
    };
}

#endif

