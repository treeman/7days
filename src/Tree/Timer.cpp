#include "Timer.hpp"

using namespace Tree;

Timer::Timer() : start_tick(0), pause_tick(0), time(0), speed( 1 ),
    is_started(false), is_paused(false)
{

}
Timer::~Timer()
{

}

void Timer::Start()
{
    if( !is_started || is_paused ) {
        start_tick = clock.GetElapsedTime();
        is_started = true;
        is_paused = false;
    }
}
void Timer::Pause()
{
    if( is_started && !is_paused ) {
        is_paused = true;
        time += GetTimeStep();
    }
}
void Timer::Stop()
{
    time = 0;
    is_started = is_paused = false;
}
void Timer::Toggle()
{
    if( !IsStarted() || IsPaused() ) {
        Start();
    }
    else {
        Pause();
    }
}

void Timer::Restart()
{
    Stop();
    Start();
}

float Timer::GetTime() const
{
    if( is_started && !is_paused ) {
        return time + GetTimeStep();
    }
    else {
        return time;
    }
}
void Timer::SetTime( float new_time )
{
    time = new_time;
    start_tick = clock.GetElapsedTime();
}

void Timer::SetSpeed( float multiplier )
{
    UpdateTimeAcc();
    speed = multiplier;
}
float Timer::GetSpeed() const
{
    return speed;
}

bool Timer::IsStarted() const
{
    return is_started;
}
bool Timer::IsPaused() const
{
    return is_started && is_paused;
}

float Timer::GetTimeStep() const
{
    return ( clock.GetElapsedTime() - start_tick ) * speed;
}
void Timer::UpdateTimeAcc()
{
    time = GetTime();
    start_tick = clock.GetElapsedTime();
}

CountDown::CountDown() : limit(0)
{

}
CountDown::CountDown( float _limit ) : limit(_limit)
{

}
CountDown::~CountDown()
{

}

void CountDown::SetLimit( float _limit )
{
    limit = _limit;
}
float CountDown::GetLimit() const
{
    return limit;
}

bool CountDown::IsDone()
{
    return GetTime() >= limit;
}

