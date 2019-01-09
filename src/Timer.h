/* Mateusz Krawczyk AAL.12 - Stacje BTS */
#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;

class Timer
{
public:
    typedef high_resolution_clock Clock;

    void start()
    {
        epoch = Clock::now();
    }
    Clock::duration time_elapsed() const
    {
        return Clock::now() - epoch;
    }
private:
    Clock::time_point epoch;
};


#endif // TIME R_H_INCLUDED
